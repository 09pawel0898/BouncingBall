#include "Renderer.h"

void Renderer::EnableBlending() const
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::DisableBlending() const
{
	GLCall(glDisable(GL_BLEND));
}