#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();

	unsigned offset = 0;
	const auto& elements = layout.GetElements();
	
	for (unsigned i = 0; i < elements.size(); ++i)
	{
		const auto& current = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(	i, 
										current.count, 
										current.type, 
										current.normalized, 
										layout.GetStride(), 
										(const void*)offset));
		offset += current.count * VertexBufferElement::GetTypeSize(current.type);
	}

}
