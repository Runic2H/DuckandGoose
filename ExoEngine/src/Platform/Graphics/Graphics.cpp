#include "empch.h"
#include "Graphics.h"

namespace EM {
	//for testing purpose
	void Graphic::Init()
	{
		m_shader.reset(new Shader("Assets/Shaders/basic.shader"));

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		m_Vbuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "position"}
		};

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		unsigned int indices[3] = { 0, 1, 2 };
		m_Ibuffer.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
	}
	void Graphic::Update()
	{
		m_shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_Ibuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Graphic::End()
	{

	}
	
}