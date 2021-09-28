#include "Renderer.h"

namespace En
{

	const Renderer Renderer::s_Instance = Renderer();
	bool Renderer::s_Initialized = false;
	glm::mat4 Renderer::s_ProjectionMat = glm::mat4();

	void Renderer::Init(uint16_t width, uint16_t height)
	{
		s_Instance.EnableBlending();
		s_ProjectionMat = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
		
		s_Instance.InitSpriteRenderer();
	}

	void Renderer::InitSpriteRenderer(void) const
	{

	}

	void Renderer::SetViewport(uint16_t width, uint16_t height) const
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::EnableBlending() const
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void Renderer::DisableBlending() const
	{
		GLCall(glDisable(GL_BLEND));
	}
}