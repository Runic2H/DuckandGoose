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

	struct RendererData
	{
		glm::vec4 QuadVertexPosition[4] = { { -0.5f, -0.5f, 0.0f, 1.0f },
											{  0.5f, -0.5f, 0.0f, 1.0f },
											{  0.5f,  0.5f, 0.0f, 1.0f },
											{ -0.5f,  0.5f, 0.0f, 1.0f } };

		static const unsigned int MaxQuads = 20000;			//max number of square or triangles can be adjust
		static const unsigned int MaxVertices = MaxQuads * 4;	//since one quard have 4 vertices we multi by 4
		static const unsigned int MaxIndices = MaxQuads * 6;	//{0, 1, 2, 2, 3, 0} 6 indices per quad


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

		//contain an array of texture
		std::array<MultiRefs<Texture>, 32> TextureUnits;
		unsigned int TextureUnitIndex = 1; // 0 = blank texture. Index to keep track of the texture



	}static r_Data;

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

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

		unsigned int* SquareIndices = new unsigned int[r_Data.MaxIndices];

		unsigned int offset = 0;
		for (int i = 0; i < r_Data.MaxIndices; i += 6)
		{
			SquareIndices[i + 0] = offset + 0;
			SquareIndices[i + 1] = offset + 1;
			SquareIndices[i + 2] = offset + 2;

			SquareIndices[i + 3] = offset + 2;
			SquareIndices[i + 4] = offset + 3;
			SquareIndices[i + 5] = offset + 0;

			offset += 4;
		}

		MultiRefs<IndexBuffer> SquareIndexBuffer = IndexBuffer::Create(SquareIndices, r_Data.MaxIndices);
		r_Data.QuadVertexArray->SetIndexBuffer(SquareIndexBuffer);
		delete[] SquareIndices;


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

	}
	void Renderer::Begin(Camera2D& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		StartBatch();
	
	}
	void Renderer::End()
	{
		Flush();
	}

	void Renderer::StartBatch()
	{
		//quad
		r_Data.QuadIndexCount = 0;
		r_Data.QuadVertexBufferPtr = r_Data.QuadVertexBufferBase; //keep track of the buffer 

		//Line
		r_Data.LineVertexCount = 0;
		r_Data.LineVertexBufferPtr = r_Data.LineVertexBufferBase;

		r_Data.TextureUnitIndex = 1;
	}
	void Renderer::Flush()
	{
		if (r_Data.QuadIndexCount)
		{
			unsigned int  QuadsDataSize = (unsigned int)((uint8_t*)r_Data.QuadVertexBufferPtr - (uint8_t*)r_Data.QuadVertexBufferBase);
			r_Data.QuadVertexBuffer->SetBufferData(r_Data.QuadVertexBufferBase, QuadsDataSize);

			//Bind All Textures
			for (int i = 0; i < r_Data.TextureUnitIndex; i++)
				r_Data.TextureUnits[i]->Bind(i);

			//reset count
			r_Data.QuadShader->Bind();
			r_Data.QuadShader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
			Renderer::DrawIndexed(r_Data.QuadVertexArray, r_Data.QuadIndexCount);
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
		}
	}
	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}
	void Renderer::ShutDown()
	{
		delete[] r_Data.QuadVertexBufferBase;
	}

	void Renderer::DrawIndexed(const MultiRefs<VertexArray>& vertexarray, unsigned int IndexCount)
	{
		vertexarray->Bind();
		unsigned int count = IndexCount ? IndexCount : vertexarray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawForLine(const MultiRefs<VertexArray>& vertexarray, unsigned int vertexCount)
	{
		vertexarray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr glm::vec2 textureCoors[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float textureIndex = 0.0f; // White Texture
		constexpr size_t quadCount = 4;

		if (r_Data.QuadIndexCount >= RendererData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < quadCount; i++)
		{
			r_Data.QuadVertexBufferPtr->Position = transform * r_Data.QuadVertexPosition[i];
			r_Data.QuadVertexBufferPtr->Color = color;
			r_Data.QuadVertexBufferPtr->TexCoord = textureCoors[i];
			r_Data.QuadVertexBufferPtr->TextureIndex = textureIndex; // blank texture
			r_Data.QuadVertexBufferPtr++;
		}
		r_Data.QuadIndexCount += 6;
	}

	void Renderer:: DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture);
	}

	void Renderer::DrawQuad(const glm::mat4& transform, const MultiRefs<Texture>& texture)
	{
		
		float t_width = texture->GetWidth(), t_height = texture->GetHeight();
		float X_index = 2.0f, Y_index = 0.0f;
		float spritewidth = t_width / X_index, spriteheight = t_height;


		float textureIndex = 0.0f;
		for (int i = 1; i < r_Data.TextureUnitIndex; i++)
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

		constexpr glm::vec2 textureCoors[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
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
	}
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}
	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
	}
	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture);
	}
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


}