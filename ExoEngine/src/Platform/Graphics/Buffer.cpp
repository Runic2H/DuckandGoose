#include "empch.h"
#include "Buffer.h"
#include "VertexBuffer.h"

namespace EM {
	MultiRefs<VertexBuffer> VertexBuffer::Create(float* data, unsigned int size)
	{
		return CreateMultiRefs<VBuffer>(data, size);
	}

	MultiRefs<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		return CreateMultiRefs<IBuffer>(indices, count);
	}
}