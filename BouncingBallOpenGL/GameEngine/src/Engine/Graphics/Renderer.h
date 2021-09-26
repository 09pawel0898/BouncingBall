#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

class Renderer
{
private:
    static Renderer m_Instance;

public:
    static Renderer& GetInstance(){ return m_Instance; }

	inline void Clear() const;

    template <typename IBDataType>
    void Draw(const VertexArray& vertexArray, const IndexBuffer<IBDataType>& indexBuffer, const Shader& shader) const;
	void EnableBlending() const;
	void DisableBlending() const;
};

inline void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

template <typename IBDataType>
void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer<IBDataType>& indexBuffer, const Shader& shader) const
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), indexBuffer.GetDataType(), nullptr));
}
