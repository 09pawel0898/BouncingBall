#include "Sprite.h"

#include "Texture.h"
#include "Renderer.h"

namespace En
{

	Sprite::Sprite()
		:	m_Position({ 0,0 }),
			m_Size({ 0,0 }),
			m_Rotation(0.0f),
			m_Texture(nullptr)
	{
		std::cout << "() ctor called\n";
	}

	Sprite::Sprite(TexturePtr texture, const glm::vec2& pos, const glm::vec2& size, float rotAngle)
		:	m_Position(pos),
			m_Size(size),
			m_Rotation(rotAngle),
			m_Texture(std::move(texture))
	{
		std::cout << "(tex,pos,size,angle) ctor called\n";
	}

	Sprite::Sprite(const Sprite& sprite)
		:	m_Position(sprite.m_Position),
			m_Size(sprite.m_Size),
			m_Rotation(sprite.m_Rotation),
			m_Texture(sprite.m_Texture)
	{
		std::cout << "copy (Sprite&) ctor called\n";
	}

	Sprite::Sprite(Sprite&& sprite) noexcept
		:	m_Texture(std::move(sprite.m_Texture)),
			m_Position(std::move(sprite.m_Position)),
			m_Size(std::move(sprite.m_Size)),
			m_Rotation(sprite.m_Rotation)
	{
		std::cout << "move (Sprite&&) ctor called\n";
	}

	Sprite& Sprite::operator=(const Sprite& rhs)
	{
		std::cout << "copy =(Sprite&) operator called\n";
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
		std::cout << "move (Sprite&&) operator called\n";
		if (this != &rhs)
		{
			m_Texture = std::move(rhs.m_Texture);
			m_Position = std::move(rhs.m_Position);
			m_Size = std::move(rhs.m_Size);
			m_Rotation = rhs.m_Rotation;
		}
		return *this;
	}
}
