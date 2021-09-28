#pragma once

#include <string>

class Texture
{
private:
	uint32_t m_RendererID = 0;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width = 0, m_Height = 0, m_BPP = 0;

public:
	Texture();
	explicit Texture(const std::string& path);
	~Texture();

	bool LoadFromFile(const std::string& path);
	void Bind(uint32_t slot = 0) const;
	void Unbind(void) const;

	inline uint16_t GetWidth(void) const  { return m_Width;  }
	inline uint16_t GetHeight(void) const { return m_Height; }

};