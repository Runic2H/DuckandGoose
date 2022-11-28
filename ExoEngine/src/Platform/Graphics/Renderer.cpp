/*!*************************************************************************
****
\file			Renderer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			02-11-2022
\brief			This file contain all the require draw call function defintion
				for our graphic. There batch rendering doing in here too.
				To maintain as less draw call as possible
****************************************************************************
***/
#include "empch.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
namespace EM {
	Singleton<Renderer::SceneData> Renderer::s_SceneData = CreateSingleton<Renderer::SceneData>();

	//whats inside a quad
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TextureIndex;
	};
	//whats inside a line
	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	//whats inside a quad with color only
	struct BoxVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};
	
	//whats inside a circle
	struct CircleVertex
	{
		glm::vec3 Wposition; //world position
		glm::vec3 Lposition; //Local position
		glm::vec4 color;
		float depth;		// the thickness
		float decline;		// fade
	};
	struct RendererData
	{
		glm::vec4 QuadVertexPosition[4] = { { -0.5f, -0.5f, 0.0f, 1.0f },
											{  0.5f, -0.5f, 0.0f, 1.0f },
											{  0.5f,  0.5f, 0.0f, 1.0f },
											{ -0.5f,  0.5f, 0.0f, 1.0f } };

		static const unsigned int MaxQuads = 20000;			//max number of square or triangles can be adjust
		static const unsigned int MaxVertices = MaxQuads * 4;	//since one quard have 4 vertices we multi by 4
		static const unsigned int MaxIndices = MaxQuads * 6;	//{0, 1, 2, 2, 3, 0} 6 indices per quad

		//for boxes without texture
		MultiRefs<VertexArray> BoxVertexArray;
		MultiRefs<VertexBuffer> BoxVertexBuffer;
		MultiRefs<Shader> BoxShader;

		unsigned int BoxIndexCount = 0;
		BoxVertex* BoxVertexBufferBase = nullptr;
		BoxVertex* BoxVertexBufferPtr = nullptr;

		//for lines
		MultiRefs<VertexArray> LineVertexArray;
		MultiRefs<VertexBuffer> LineVertexBuffer;
		MultiRefs<Shader> LineShader;

		unsigned int LineVertexCount = 0;
		LineVertex* LineVertexBufferBase = nullptr;
		LineVertex* LineVertexBufferPtr = nullptr;

		//for quads
		MultiRefs<VertexArray> QuadVertexArray;
		MultiRefs<VertexBuffer> QuadVertexBuffer;
		MultiRefs<Texture> BlankTexture;
		MultiRefs<Shader> QuadShader;

		unsigned int QuadIndexCount = 0; //keep track of how many indices need to draw when flushes down
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		//for circle
		MultiRefs<VertexArray> CircleVertexArray;
		MultiRefs<VertexBuffer> CircleVertexBuffer;
		MultiRefs<Shader> CircleShader;

		unsigned int CircleIndexCount = 0;
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;

		//contain an array of texture
		std::array<MultiRefs<Texture>, 32> TextureUnits;
		unsigned int TextureUnitIndex = 1; // 0 = blank texture. Index to keep track of the texture

		Renderer::Information Infos;

	}static r_Data;

	/*!*************************************************************************
	Set Clear Color
	****************************************************************************/
	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	/*!*************************************************************************
	Clear buffer
	****************************************************************************/
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/*!*************************************************************************
	Init loop of Renderer
	****************************************************************************/
	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		/// FOR QUADS
		r_Data.QuadVertexArray = VertexArray::Create();

		r_Data.QuadVertexBuffer = VertexBuffer::Create(r_Data.MaxVertices * sizeof(QuadVertex));
		r_Data.QuadVertexBuffer->SetLayout({ { ShaderDataType::Float3, "position" },
											{ ShaderDataType::Float4, "a_Color" },
											{ ShaderDataType::Float2, "a_TexCoord" },
											{ ShaderDataType::Float, "a_TextureIndex"}
									  });
		r_Data.QuadVertexArray->AddVertexBuffer(r_Data.QuadVertexBuffer);
		
		r_Data.QuadVertexBufferBase = new QuadVertex[r_Data.MaxVertices];

		unsigned int* QuadIndices = new unsigned int[r_Data.MaxIndices];

		unsigned int offset = 0;
		for (int i = 0; i < r_Data.MaxIndices; i += 6)
		{
			QuadIndices[i + 0] = offset + 0;
			QuadIndices[i + 1] = offset + 1;
			QuadIndices[i + 2] = offset + 2;

			QuadIndices[i + 3] = offset + 2;
			QuadIndices[i + 4] = offset + 3;
			QuadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		MultiRefs<IndexBuffer> QuadIndexBuffer = IndexBuffer::Create(QuadIndices, r_Data.MaxIndices);
		r_Data.QuadVertexArray->SetIndexBuffer(QuadIndexBuffer);
		delete[] QuadIndices;


		//setting empty texture in unit 0
		r_Data.BlankTexture = ResourceManager::GenTexture(1, 1);
		unsigned int BlankTextureData = 0xffffffff;
		r_Data.BlankTexture->SetTextureData(&BlankTextureData, sizeof(unsigned int));


		//Shader
		r_Data.QuadShader = ResourceManager::GetShader("QuadShader");
		int TextureSamplers[32];
		for (int i = 0; i < 32; i++)
			TextureSamplers[i] = i;
		r_Data.QuadShader->Bind();
		r_Data.QuadShader->SetUniform("u_Texture", TextureSamplers, 32);

		//set first texture unit 0 to be blanktexture
		r_Data.TextureUnits[0] = r_Data.BlankTexture;
		


		//// FOR drawing LINE and also debug drawing
		r_Data.LineVertexArray = VertexArray::Create();
		r_Data.LineVertexBuffer = VertexBuffer::Create(r_Data.MaxVertices * sizeof(LineVertex));
		r_Data.LineVertexBuffer->SetLayout({ 
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "a_Color"}
			});

		r_Data.LineVertexArray->AddVertexBuffer(r_Data.LineVertexBuffer);
		r_Data.LineVertexBufferBase = new LineVertex[r_Data.MaxVertices];

		r_Data.LineShader = ResourceManager::GetShader("LineShader");

		/// For boxes without texture

		r_Data.BoxVertexArray = VertexArray::Create();

		r_Data.BoxVertexBuffer = VertexBuffer::Create(r_Data.MaxVertices * sizeof(BoxVertex));
		r_Data.BoxVertexBuffer->SetLayout({ { ShaderDataType::Float3, "position" },
											{ ShaderDataType::Float4, "a_Color" },
			});
		r_Data.BoxVertexArray->AddVertexBuffer(r_Data.BoxVertexBuffer);

		r_Data.BoxVertexBufferBase = new BoxVertex[r_Data.MaxVertices];

		unsigned int* BoxIndices = new unsigned int[r_Data.MaxIndices];

		unsigned int offsetBox = 0;
		for (int i = 0; i < r_Data.MaxIndices; i += 6)
		{
			BoxIndices[i + 0] = offsetBox + 0;
			BoxIndices[i + 1] = offsetBox + 1;
			BoxIndices[i + 2] = offsetBox + 2;

			BoxIndices[i + 3] = offsetBox + 2;
			BoxIndices[i + 4] = offsetBox + 3;
			BoxIndices[i + 5] = offsetBox + 0;

			offsetBox += 4;
		}

		MultiRefs<IndexBuffer> BoxIndexBuffer = IndexBuffer::Create(BoxIndices, r_Data.MaxIndices);
		r_Data.BoxVertexArray->SetIndexBuffer(BoxIndexBuffer);
		delete[] BoxIndices;
		//box shader
		r_Data.BoxShader = ResourceManager::GetShader("LineShader");

		/// For Circle
		r_Data.CircleVertexArray = VertexArray::Create();

		r_Data.CircleVertexBuffer = VertexBuffer::Create(r_Data.MaxVertices * sizeof(CircleVertex));
		r_Data.CircleVertexBuffer->SetLayout({ { ShaderDataType::Float3, "a_WorldPosition" },
			{ ShaderDataType::Float3, "a_LocalPosition" },
			{ ShaderDataType::Float4, "a_Color"         },
			{ ShaderDataType::Float,  "a_Depth"     },
			{ ShaderDataType::Float,  "a_Decline"  },
			});
		r_Data.CircleVertexArray->AddVertexBuffer(r_Data.CircleVertexBuffer);
		r_Data.CircleVertexArray->SetIndexBuffer(QuadIndexBuffer);  //use quad index
		r_Data.CircleVertexBufferBase = new CircleVertex[r_Data.MaxVertices];
		r_Data.CircleShader = ResourceManager::GetShader("CircleShader");
	}

	/*!*************************************************************************
	Start rendering
	****************************************************************************/
	void Renderer::Begin(Camera2D& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		StartBatch();
	
	}

	/*!*************************************************************************
	End loop of Renderer
	****************************************************************************/
	void Renderer::End()
	{
		Flush();
	}

	/*!*************************************************************************
	Start batch rendering
	****************************************************************************/
	void Renderer::StartBatch()
	{
		//quad
		r_Data.QuadIndexCount = 0;
		r_Data.QuadVertexBufferPtr = r_Data.QuadVertexBufferBase; //keep track of the buffer 
		r_Data.TextureUnitIndex = 1;

		//Line
		r_Data.LineVertexCount = 0;
		r_Data.LineVertexBufferPtr = r_Data.LineVertexBufferBase;

		//Box
		r_Data.BoxIndexCount = 0;
		r_Data.BoxVertexBufferPtr = r_Data.BoxVertexBufferBase;

		//Circle
		r_Data.CircleIndexCount = 0;
		r_Data.CircleVertexBufferPtr = r_Data.CircleVertexBufferBase;
		
	}

	/*!*************************************************************************
	Flush is like pushing all the set buffer data into the GPU
	****************************************************************************/
	void Renderer::Flush()
	{
		//Quads
		if (r_Data.QuadIndexCount)
		{
			unsigned int  QuadsDataSize = (unsigned int)((uint8_t*)r_Data.QuadVertexBufferPtr - (uint8_t*)r_Data.QuadVertexBufferBase);
			r_Data.QuadVertexBuffer->SetBufferData(r_Data.QuadVertexBufferBase, QuadsDataSize);

			//Bind All Textures
			for (unsigned int i = 0; i < r_Data.TextureUnitIndex; i++)
				r_Data.TextureUnits[i]->Bind(i);

			//reset count
			r_Data.QuadShader->Bind();
			r_Data.QuadShader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
			Renderer::DrawIndexed(r_Data.QuadVertexArray, r_Data.QuadIndexCount);
			r_Data.Infos.n_DrawCalls++;
		}
		//Line
		if (r_Data.LineVertexCount)
		{
			unsigned int LineDataSize = (unsigned int)((uint8_t*)r_Data.LineVertexBufferPtr - (uint8_t*)r_Data.LineVertexBufferBase);
			r_Data.LineVertexBuffer->SetBufferData(r_Data.LineVertexBufferBase, LineDataSize);

			r_Data.LineShader->Bind();
			r_Data.LineShader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
			glLineWidth(1.0f);
			Renderer::DrawForLine(r_Data.LineVertexArray, r_Data.LineVertexCount);
			r_Data.Infos.n_DrawCalls++;
		}
		//Box
		if (r_Data.BoxIndexCount)
		{
			unsigned int  BoxDataSize = (unsigned int)((uint8_t*)r_Data.BoxVertexBufferPtr - (uint8_t*)r_Data.BoxVertexBufferBase);
			r_Data.BoxVertexBuffer->SetBufferData(r_Data.BoxVertexBufferBase, BoxDataSize);

			//reset count
			r_Data.BoxShader->Bind();
			r_Data.BoxShader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
			Renderer::DrawIndexed(r_Data.BoxVertexArray, r_Data.BoxIndexCount);
			r_Data.Infos.n_DrawCalls++;
		}
		if (r_Data.CircleIndexCount)
		{
			unsigned int  CircleDataSize = (unsigned int)((uint8_t*)r_Data.CircleVertexBufferPtr - (uint8_t*)r_Data.CircleVertexBufferBase);
			r_Data.CircleVertexBuffer->SetBufferData(r_Data.CircleVertexBufferBase, CircleDataSize);

			//reset count
			r_Data.CircleShader->Bind();
			r_Data.CircleShader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
			Renderer::DrawIndexed(r_Data.CircleVertexArray, r_Data.CircleIndexCount);
			r_Data.Infos.n_DrawCalls++;
		}
	}

	/*!*************************************************************************
	When the set max amount of buffer exceed the max limit, next batch will be called
	****************************************************************************/
	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}

	/*!*************************************************************************
	Release the buffer set in the gpu
	****************************************************************************/
	void Renderer::ShutDown()
	{
		delete[] r_Data.QuadVertexBufferBase;
		delete[] r_Data.BoxVertexBufferBase;
	}
	/*!*************************************************************************
	Set and bind the vertexarray to tell the gpu how to draw the  quad obj
	****************************************************************************/
	void Renderer::DrawIndexed(const MultiRefs<VertexArray>& vertexarray, unsigned int IndexCount)
	{
		vertexarray->Bind();
		unsigned int count = IndexCount ? IndexCount : vertexarray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	/*!*************************************************************************
	Set and bind the vertexarray to tell the gpu how to draw the line obj
	****************************************************************************/
	void Renderer::DrawForLine(const MultiRefs<VertexArray>& vertexarray, unsigned int vertexCount)
	{
		vertexarray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
	/*!*************************************************************************
	Overload function for Draw Quad using vec2 position with no texture just shader
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	/*!*************************************************************************
	Overload function for Draw Quad using vec3 position with no texture just shader
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}
	/*!*************************************************************************
	Overload function for Draw Quad using transform with no texture just shader
	****************************************************************************/
	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr size_t BoxCount = 4;

		if (r_Data.BoxIndexCount >= RendererData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < BoxCount; i++)
		{
			r_Data.BoxVertexBufferPtr->Position = transform * r_Data.QuadVertexPosition[i];
			r_Data.BoxVertexBufferPtr->Color = color;
			r_Data.BoxVertexBufferPtr++;
		}
		r_Data.BoxIndexCount += 6;

		r_Data.Infos.n_Quad++;
	}
	/*!*************************************************************************
	Overload function for Draw Quad using vec2 position with texture
	****************************************************************************/
	void Renderer:: DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	
	/*!*************************************************************************
Overload function for Draw Quad using vec3 position with texture
****************************************************************************/
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture);
	}

	/*!*************************************************************************
	Overload function for Draw Quad using transform with texture
	****************************************************************************/
	void Renderer::DrawQuad(const glm::mat4& transform, const MultiRefs<Texture>& texture)
	{

		float textureIndex = 0.0f;
		for (unsigned int i = 1; i < r_Data.TextureUnitIndex; i++)
		{
			if (*r_Data.TextureUnits[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (r_Data.TextureUnitIndex >= 32)
				NextBatch();

			textureIndex = (float)r_Data.TextureUnitIndex;
			r_Data.TextureUnits[r_Data.TextureUnitIndex] = texture;
			r_Data.TextureUnitIndex++;
		}
		constexpr glm::vec2 textureCoors[] = { { 0.0f , 0.0f }, { 1.f, 0.0f }, { 1.f, 1.0f },{ 0.f,1.0f} };
		constexpr size_t quadCount = 4;
		for (size_t i = 0; i < quadCount; i++)
		{
			r_Data.QuadVertexBufferPtr->Position = transform * r_Data.QuadVertexPosition[i];
			r_Data.QuadVertexBufferPtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			r_Data.QuadVertexBufferPtr->TexCoord = textureCoors[i];
			r_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
			r_Data.QuadVertexBufferPtr++;
		}
		r_Data.QuadIndexCount += 6;

		r_Data.Infos.n_Quad++;
	}
	/*!*************************************************************************
	Overload function for Draw Quad using vec2 position with no texture just shader and rotation 
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	/*!*************************************************************************
	Overload function for Draw Quad using vec3 position with no texture just shader and rotation
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	/*!*************************************************************************
	Overload function for Draw Quad using vec2 position with rotation and texture
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
	}

	/*!*************************************************************************
	Overload function for Draw Quad using vec3 position with rotation and texture
	****************************************************************************/
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture);
	}
	/*!*************************************************************************
	Overload function for Draw Quad using vec2 position with rotation and spritesheet
	****************************************************************************/
	void Renderer::DrawSprite(const glm::vec2& position, const glm::vec2& size, const float& rotation, const MultiRefs<SpriteRender>& sprite)
	{
		DrawSprite({ position.x, position.y, 0.0f }, size, rotation, sprite);
	}

	/*!*************************************************************************
	Overload function for Draw Quad using vec3 position with rotation and spritesheet
	****************************************************************************/
	void Renderer::DrawSprite(const glm::vec3& position, const glm::vec2& size, const float& rotation, const MultiRefs<SpriteRender>& sprite)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawSprite(transform, sprite);
	}
	/*!*************************************************************************
	Overload function for Draw Quad using mat4 transform with rotation and spritesheet
	****************************************************************************/
	void Renderer::DrawSprite(const glm::mat4& transform, const MultiRefs<SpriteRender>& sprite)
	{
		float textureIndex = 0.0f;
		for (unsigned int i = 1; i < r_Data.TextureUnitIndex; i++)
		{
			if (*r_Data.TextureUnits[i] == *sprite->GetTexture())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (r_Data.TextureUnitIndex >= 32)
				NextBatch();

			textureIndex = (float)r_Data.TextureUnitIndex;
			r_Data.TextureUnits[r_Data.TextureUnitIndex] = sprite->GetTexture();
			r_Data.TextureUnitIndex++;
		}
		const glm::vec2* textureCoors = sprite->GetTexCoords();
		constexpr size_t quadCount = 4;

		for (size_t i = 0; i < quadCount; i++)
		{
			r_Data.QuadVertexBufferPtr->Position =  transform * r_Data.QuadVertexPosition[i];
			r_Data.QuadVertexBufferPtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			r_Data.QuadVertexBufferPtr->TexCoord = textureCoors[i];
			r_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
			r_Data.QuadVertexBufferPtr++;
		}
		r_Data.QuadIndexCount += 6;
		r_Data.Infos.n_Quad++;
	}
	/*!*************************************************************************
	This function draw line using shaders
	****************************************************************************/
	void Renderer::DrawLine(const glm::vec3& position0, const glm::vec3& position1, const glm::vec4& color)
	{
		r_Data.LineVertexBufferPtr->Position = position0;
		r_Data.LineVertexBufferPtr->Color = color;
		r_Data.LineVertexBufferPtr++;

		r_Data.LineVertexBufferPtr->Position = position1;
		r_Data.LineVertexBufferPtr->Color = color;
		r_Data.LineVertexBufferPtr++;

		r_Data.LineVertexCount += 2;
	}
	/*!*************************************************************************
	This function draw rect using draw line 4 times
	****************************************************************************/
	void Renderer::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::vec3 p0 = glm::vec3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
		glm::vec3 p1 = glm::vec3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
		glm::vec3 p2 = glm::vec3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
		glm::vec3 p3 = glm::vec3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);

		DrawLine(p0, p1, color);
		DrawLine(p1, p2, color);
		DrawLine(p2, p3, color);
		DrawLine(p3, p0, color);
	}
	/*!*************************************************************************
	This function draw circle using shader
	****************************************************************************/
	void Renderer::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float depth, float decline)
	{
		for (size_t i = 0; i < 4; i++)
		{
			r_Data.CircleVertexBufferPtr->Wposition = transform * r_Data.QuadVertexPosition[i];
			r_Data.CircleVertexBufferPtr->Lposition = r_Data.QuadVertexPosition[i] * 2.0f;
			r_Data.CircleVertexBufferPtr->color = color;
			r_Data.CircleVertexBufferPtr->depth = depth;
			r_Data.CircleVertexBufferPtr->decline= decline;
			r_Data.CircleVertexBufferPtr++;
		}

		r_Data.CircleIndexCount += 6;

		r_Data.Infos.n_Quad++;
	}
	/*!*************************************************************************
	Reset the drawing information such as draw call, index used , buffer used.
	****************************************************************************/
	void Renderer::ResetInfo()
	{
		memset(&r_Data.Infos, 0, sizeof(Information));
	}
	/*!*************************************************************************
	Get the drawing information such as draw call, index used , buffer used.
	****************************************************************************/
	Renderer::Information Renderer::GetInfo()
	{
		return r_Data.Infos;
	}


}