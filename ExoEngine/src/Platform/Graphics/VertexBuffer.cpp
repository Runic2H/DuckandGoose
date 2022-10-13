/*!*************************************************************************
****
\file			VertexBuffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file handle vertexbuffer, indexbuffer, vertaxarray

****************************************************************************
***/
#include "empch.h"
#include "VertexBuffer.h"

//new 
#include "GL/glew.h"
namespace EM{
	VBuffer::VBuffer(float* vertices, unsigned int size)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VBuffer::~VBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	void VBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void VBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	////////////INDEX BUFFER///////////
	IBuffer::IBuffer(unsigned int* indices, unsigned int count)
		:m_count(count)
	{
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	IBuffer::~IBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}
	void IBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}
	void IBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
