#pragma once

#include "../Core/Core.h"

namespace En
{
	template <typename IntType>
	inline static constexpr bool IsGoodType()
	{
		return (std::is_same<IntType, uint32_t>::value ||
			std::is_same<IntType, uint16_t>::value) ? true : false;
	}

	template <typename IntType = uint32_t>
	class IndexBuffer
	{
		static_assert(IsGoodType<IntType>(), "IndexBuffer may contain data with wrong type");
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		GLenum m_DataType;
	public:
		explicit IndexBuffer(const std::vector<IntType>& data);

		~IndexBuffer();

		inline uint32_t GetCount() const { return m_Count; }
		inline GLenum GetDataType() const { return m_DataType; }
		inline void Bind() const;
		inline void Unbind() const;
	};

	template <typename IntType>
	IndexBuffer<IntType>::IndexBuffer(const std::vector<IntType>& data)
		: m_Count(data.size())
	{
		m_DataType = GetGLEnumFromType<IntType>();
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(IntType), data.data(), GL_STATIC_DRAW));
	}

	template <typename IntType>
	IndexBuffer<IntType>::~IndexBuffer()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	template <typename IntType>
	inline void IndexBuffer<IntType>::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	template <typename IntType>
	inline void IndexBuffer<IntType>::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}