#pragma once

#include "../Core/Core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace En
{
	class VertexArray
	{
	private:
		uint32_t m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

		inline void Bind() const;
		inline void Unbind() const;
	};

	inline void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	inline void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}