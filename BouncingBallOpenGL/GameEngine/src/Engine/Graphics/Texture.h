#pragma once

#include "Renderer.h"

class Texture
{
private:
	uint32_t m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width = 0, m_Height = 0, m_BPP = 0;

public:
	explicit Texture(const std::string& path);
	~Texture();

	inline void Bind(uint32_t slot = 0) const;
	inline void Unbind() const;

	inline uint16_t GetWidth() const  { return m_Width;  }
	inline uint16_t GetHeight() const { return m_Height; }

};

inline void Texture::Bind(uint32_t slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

inline void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}