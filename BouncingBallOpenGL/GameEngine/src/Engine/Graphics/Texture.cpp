#include "Texture.h"

#include "stb_image/stb_image.h"
#include "../Core/Core.h"
#include "../Core/Debug.h"

Texture::Texture()
	:	m_FilePath(""),
		m_LocalBuffer(nullptr)
{}

Texture::Texture(const std::string& path)
	:	m_FilePath(path),
		m_LocalBuffer(nullptr)
{
	LoadFromFile(path);
}

Texture::~Texture(void)
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

bool Texture::LoadFromFile(const std::string& path)
{
	if (m_RendererID != 0)
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}
	
	m_FilePath = path;
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (!m_LocalBuffer)
	{
		EN_DEBUGMSG("%s%s%s", "[Texture] Can't load a texture from file '",path.c_str(),"'\n");
		return false;
	}
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	Unbind();
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		return true;
	}
	return false;
}

void Texture::Bind(uint32_t slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind(void) const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}