#pragma once
#include "Platform/System/System.h"
#include "Platform/Graphics/VertexBuffer.h"
#include "Platform/Graphics/Shader.h"

namespace EM {

	class Graphic : public System
	{
	public:

		//For Debugging Purposes
		virtual std::string GetName() { return "graphic"; }

		virtual void Init() override;
		virtual void Update() override;
		virtual void End() override;
	private:
		//for testing
		unsigned int m_VertexArray{ 0 };
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexBuffer> m_Vbuffer;
		std::unique_ptr<IndexBuffer> m_Ibuffer;
	};
}