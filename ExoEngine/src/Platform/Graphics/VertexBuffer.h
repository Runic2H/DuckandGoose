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

		unsigned int GetCount() const { return m_count; }

	private:

		unsigned int m_RenderID;
		unsigned int m_count;
	};

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 8;
			case ShaderDataType::Float3:	return 12;
			case ShaderDataType::Float4:	return 16;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 8;
			case ShaderDataType::Int3:		return 12;
			case ShaderDataType::Int4:		return 16;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		EM_EXO_ASSERT(false, "Unknow Data type!");
		return 0;
	}

	//////////buffer elements
	class BufferElements
	{
	public:

		BufferElements() = default;
		BufferElements(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}
	public:
		ShaderDataType Type;
		std::string Name;
		size_t Size;
		unsigned int Offset;
		bool Normalized;
	};


	//bufferlayout
	class BufferLayout 
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElements>& element)
		: m_Elements(element)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElements>& GetElements() const { return m_Elements; } //getter

	private:
		void CalculateOffsetAndStride()
		{
			unsigned int offset = 0;
			m_stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElements> m_Elements;
		unsigned int m_stride;
	};
}