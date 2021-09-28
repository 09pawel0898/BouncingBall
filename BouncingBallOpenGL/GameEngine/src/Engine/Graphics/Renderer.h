#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Sprite.h"

namespace En
{
	class Renderer
	{
	private:
		static const Renderer s_Instance;
		static bool s_Initialized;
		Renderer() = default;

	public:
		inline static const Renderer* Instance() { return (s_Initialized) ? &s_Instance : nullptr; }
		static void Init(uint16_t width, uint16_t height);

	private:
		static glm::mat4 s_ProjectionMat;
		void InitSpriteRenderer(void) const;

	public:
		inline void Clear(void) const;

		template <typename IBDataType>
		void Draw(const VertexArray& vertexArray, const IndexBuffer<IBDataType>& indexBuffer, const Shader& shader) const;
		void Draw(const Sprite& sprite);

		void SetViewport(uint16_t width, uint16_t height) const;
		void SetClearColor(const glm::vec4& color) const;
		void EnableBlending(void) const;
		void DisableBlending(void) const;
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
}
