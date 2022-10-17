#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"

#include "Camera2D.h"
namespace EM {

	class Renderer
	{
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();

		//render call
		static void Init();
		static void ShutDown();

		static void Begin(Camera2D& camera);
		static void End();
		static void Flush();
		

		static void DrawIndexed(const MultiRefs<VertexArray>& vertexarray, unsigned int IndexCount = 0);
		static void DrawForLine(const MultiRefs<VertexArray>& vertexarray, unsigned int vertexCount);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::mat4& transform, const MultiRefs<Texture>& texture);

		
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture);

		
		void DrawLine(const glm::vec3& position0, const glm::vec3& position1, const glm::vec4& color);
		void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static Singleton<SceneData> s_SceneData;

	private:
		static void StartBatch();
		static void NextBatch();
	};
}