#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
//#include "Shader.h"

#include "Camera2D.h"
namespace EM {

	class Renderer
	{
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();

		//render call
		void Init();
		static void Begin(Camera2D& camera);
		static void End();

		void DrawIndexed(const MultiRefs<VertexArray>& vertexarray, const MultiRefs<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

		void DrawIndexForLine(const MultiRefs<VertexArray>& vertexarray, const MultiRefs<Shader>& shader, const glm::mat4& transform);
		void DrawLine(const glm::vec3& position0, glm::vec3& position1, const glm::vec4 color);
		void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static Singleton<SceneData> s_SceneData;
		//static Singleton<Renderer> m_Renderer;
	};
}