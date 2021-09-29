#include "Sprite.h"

#include "Texture.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"

#include "Shader.h"
#include "RendererData.h"

namespace En
{
	std::unique_ptr<SpriteRendererData> Sprite::s_RendererData = nullptr;

	Sprite::Sprite()
		:	m_Position({ 0,0 }),
			m_Size({ 0,0 }),
			m_Rotation(0.0f),
			m_Texture(nullptr)
	{}

	Sprite::Sprite(TexturePtr texture, const glm::vec2& pos, float rotAngle)
		:	m_Texture(std::move(texture)),
			m_Position(pos),
			m_Size(m_Texture->GetWidth(),m_Texture->GetHeight()),
			m_Rotation(rotAngle)
			
	{}

	Sprite::Sprite(const Sprite& sprite)
		:	m_Position(sprite.m_Position),
			m_Size(sprite.m_Size),
			m_Rotation(sprite.m_Rotation),
			m_Texture(sprite.m_Texture)
	{}

	Sprite::Sprite(Sprite&& sprite) noexcept
		:	m_Texture(std::move(sprite.m_Texture)),
			m_Position(std::move(sprite.m_Position)),
			m_Size(std::move(sprite.m_Size)),
			m_Rotation(sprite.m_Rotation)
	{}

	Sprite& Sprite::operator=(const Sprite& rhs)
	{
		if (this != &rhs)
		{
			m_Position = rhs.m_Position;
			m_Size = rhs.m_Size;
			m_Rotation = rhs.m_Rotation;
			m_Texture = rhs.m_Texture;
		}
		return *this;
	}

	Sprite& Sprite::operator=(Sprite&& rhs) noexcept
	{
		if (this != &rhs)
		{
			m_Texture = std::move(rhs.m_Texture);
			m_Position = std::move(rhs.m_Position);
			m_Size = std::move(rhs.m_Size);
			m_Rotation = rhs.m_Rotation;
		}
		return *this;
	}
	
	void Sprite::SetRotation(float rot)
	{
		m_Rotation = (float)fmod(rot, 360);
		if (m_Rotation < 0)
			m_Rotation += 360.0f;
	}
}
