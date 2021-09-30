#pragma once

#include "../Core/Core.h"

namespace En
{
	struct VertexBufferElement
	{
		uint8_t count;
		GLenum type;
		unsigned char normalized;

		static constexpr unsigned GetTypeSize(GLenum type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
			EN_ASSERT(false);
			return 0;
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned m_Stride;

	public:
		VertexBufferLayout()
			: m_Stride(0)
		{}

		template<typename T>
		void Push(uint8_t count) { static_assert(false); }
		template <> inline void Push<float>(uint8_t count);
		template <> inline void Push<unsigned>(uint8_t count);
		template <> inline void Push<unsigned char>(uint8_t count);

		inline const std::vector<VertexBufferElement>& GetElements() const
		{
			return m_Elements;
		}
		inline unsigned GetStride() const
		{
			return m_Stride;
		}
	};

	template <>
	inline void VertexBufferLayout::Push<float>(uint8_t count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	inline void VertexBufferLayout::Push<unsigned>(uint8_t count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	inline void VertexBufferLayout::Push<unsigned char>(uint8_t count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}
}