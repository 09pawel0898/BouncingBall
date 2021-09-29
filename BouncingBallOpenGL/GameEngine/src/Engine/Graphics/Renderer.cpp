#include "Renderer.h"
#include "RendererData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace En
{
	glm::mat4 Renderer::s_ProjectionMat = glm::mat4();

	void Renderer::Init(uint16_t width, uint16_t height)
	{

		EnableBlending();
		s_ProjectionMat = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
		InitSpriteRenderer();
	}

	void Renderer::InitSpriteRenderer(void)
	{
		auto& spriteRendererData = Sprite::GetRendererData();
		spriteRendererData = std::make_unique<SpriteRendererData>();
		spriteRendererData->shader->Bind();
		spriteRendererData->shader->SetUniform1i("u_Texture", 0);
	}

	void Renderer::Draw(const Sprite& sprite)
	{
		glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(sprite.GetPosition(), 0.0f)) *
							 glm::rotate(glm::mat4(1.0f), glm::radians(sprite.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f)) *
							 glm::scale(glm::mat4(1.0f), glm::vec3(sprite.GetSize(), 1.0f));

		auto& spriteRendererData = Sprite::GetRendererData();
		sprite.BindTexture(0);

		Draw(	*spriteRendererData->vertexArray,
				*spriteRendererData->indexBuffer,
				*spriteRendererData->shader,
				s_ProjectionMat * modelMat
			);
	}

	void Renderer::SetViewport(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::EnableBlending()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void Renderer::DisableBlending()
	{
		GLCall(glDisable(GL_BLEND));
	}
}