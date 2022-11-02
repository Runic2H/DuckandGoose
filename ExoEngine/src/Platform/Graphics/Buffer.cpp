/*!*************************************************************************
****
\file			Buffer.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			02-11-2022
\brief			This file contain all the helper function needed for buffer
				optimatization so that it will be easier to handle the buffer
				data
****************************************************************************
***/
#include "empch.h"
#include "Buffer.h"
#include "VertexBuffer.h"

namespace EM {
	MultiRefs<VertexBuffer> VertexBuffer::Create(uint32_t size)//Dynamic Draw
	{
		return CreateMultiRefs<VBuffer>(size);
	}

	MultiRefs<VertexBuffer> VertexBuffer::Create(float* data, unsigned int size)//Static Draw
	{
		return CreateMultiRefs<VBuffer>(data, size);
	}

	MultiRefs<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		return CreateMultiRefs<IBuffer>(indices, count);
	}
}