#pragma once

namespace EM
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	private:

		unsigned int m_RenderID;
	};


	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:

		unsigned int m_RenderID;
		unsigned int m_count;
	};

}