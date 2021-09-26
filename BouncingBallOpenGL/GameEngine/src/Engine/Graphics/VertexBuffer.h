#pragma once

#include "../Core/Core.h"


class VertexBuffer
{
private:
	uint32_t m_RendererID;

public:
	VertexBuffer(const std::vector<float>& data, size_t size);
	~VertexBuffer();

	inline void Bind() const;
	inline void Unbind() const;
};

inline void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

inline void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}