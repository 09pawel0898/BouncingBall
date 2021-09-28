#include "Sprite.h"

#include "Texture.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace En
{
	struct SpriteRendererData
	{
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> vertexArray;
		SpriteRendererData()
			:	shader(std::make_unique<Shader>("res/shaders/sprite.glsl")),
				vertexArray(std::make_unique<VertexArray>())
		{}
	};

	SpriteRendererData Sprite::s_RendererData = SpriteRendererData();

	Sprite::Sprite()
		:	m_Position({ 0,0 }),
			m_Size({ 0,0 }),
			m_Rotation(0.0f),
			m_Texture(nullptr)
	{}

	Sprite::Sprite(TexturePtr texture, const glm::vec2& pos, const glm::vec2& size, float rotAngle)
		:	m_Position(pos),
			m_Size(size),
			m_Rotation(rotAngle),
			m_Texture(std::move(texture))
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
