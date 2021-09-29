#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Sprite.h"

namespace En
{
	class Renderer
	{
	public:
		static void Init(uint16_t width, uint16_t height);

	private:
		static glm::mat4 s_ProjectionMat;
		static void InitSpriteRenderer(void);

	public:
		inline static void Clear(void);

		template <typename IBDataType>
		static void Draw(const VertexArray& vertexArray, const IndexBuffer<IBDataType>& indexBuffer, const Shader& shader, const glm::mat4& mvp);
		static void Draw(const Sprite& sprite);

		static void SetViewport(uint16_t width, uint16_t height);
		static void SetClearColor(const glm::vec4& color);
		static void EnableBlending(void);
		static void DisableBlending(void);
	};

	inline void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	template <typename IBDataType>
	void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer<IBDataType>& indexBuffer, const Shader& shader, const glm::mat4& mvp)
	{
		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);
		vertexArray.Bind();
		indexBuffer.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), indexBuffer.GetDataType(), nullptr));
	}
}
