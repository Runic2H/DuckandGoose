#include "empch.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
namespace EM {
	Singleton<Renderer::SceneData> Renderer::s_SceneData = CreateSingleton<Renderer::SceneData>();

	struct RendererData
	{
		MultiRefs<VertexArray> QuadVertexArray;
		MultiRefs<Shader> FlatShader;
		MultiRefs<Shader> TextureShader;
		//MultiRefs<Texture> Texture;

		MultiRefs<VertexArray> LineVertexArray;
		MultiRefs<Shader> LineShader;

	} *r_Data;
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
		
		r_Data = new RendererData;
		r_Data->QuadVertexArray = VertexArray::Create();
		float SquareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,//0 per vertex->
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//1
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,//2
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f //3
		};

		MultiRefs<VertexBuffer> SquareVertexBuffer = VertexBuffer::Create(SquareVertices, sizeof(SquareVertices));
		SquareVertexBuffer->SetLayout({ { ShaderDataType::Float3, "position" },
										{ ShaderDataType::Float2, "a_TexCoord" } 
									  });
		r_Data->QuadVertexArray->AddVertexBuffer(SquareVertexBuffer);
	
		unsigned int SquareIndices[] = { 0, 1, 2,
										 2, 3, 0 };
		
		MultiRefs<IndexBuffer> SquareIndexBuffer = IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(unsigned int));
		r_Data->QuadVertexArray->SetIndexBuffer(SquareIndexBuffer);
		r_Data->FlatShader = ResourceManager::GetShader("BasicShader");
		r_Data->TextureShader = ResourceManager::GetShader("TextureShader");
		

		//for drawing line and also debug drawing
		r_Data->LineVertexArray = VertexArray::Create();
		float LineVertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//0 per vertex->
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f//1
		};
		MultiRefs<VertexBuffer> LineVertexBuffer = VertexBuffer::Create(LineVertices, sizeof(LineVertices));
		LineVertexBuffer->SetLayout({ { ShaderDataType::Float3, "position" },
										{ ShaderDataType::Float4, "a_Color" }
			});
		r_Data->LineVertexArray->AddVertexBuffer(LineVertexBuffer);
		unsigned int LineIndices[] = { 0, 1 };
		MultiRefs<IndexBuffer> LineIndexBuffer = IndexBuffer::Create(LineIndices, sizeof(LineIndices) / sizeof(unsigned int));
		r_Data->LineVertexArray->SetIndexBuffer(LineIndexBuffer);
		r_Data->LineShader = ResourceManager::GetShader("LineShader");
	
	}
	void Renderer::Begin(Camera2D& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::End()
	{
		delete r_Data;
	}


	void Renderer::DrawIndexed(const MultiRefs<VertexArray>& vertexarray, const MultiRefs<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniform("u_Transform", transform);

		vertexarray->Bind();
		glDrawElements(GL_TRIANGLES, vertexarray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		r_Data->FlatShader->SetUniform("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawIndexed(r_Data->QuadVertexArray, r_Data->FlatShader, transform);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		r_Data->FlatShader->SetUniform("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
					glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})*
					glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawIndexed(r_Data->QuadVertexArray, r_Data->FlatShader, transform);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture)
	{
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawIndexed(r_Data->QuadVertexArray, r_Data->TextureShader, transform);
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture, const glm::vec4& color)
	{
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
				glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
				glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawIndexed(r_Data->QuadVertexArray, r_Data->TextureShader, transform);
	}
	
	void Renderer::DrawIndexForLine(const MultiRefs<VertexArray>& vertexarray, const MultiRefs<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniform("u_Transform", transform);
		vertexarray->Bind();
		glLineWidth(2.0f);
		glDrawArrays(GL_LINES, 0, vertexarray->GetIndexBuffer()->GetCount());
	}

	void Renderer::DrawLine(const glm::vec3& position0, glm::vec3& position1, const glm::vec4 color)
	{
		r_Data->LineShader->SetUniform("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position1 - position0);
		DrawIndexForLine(r_Data->LineVertexArray, r_Data->LineShader, transform);
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