#pragma once

class Texture;

#include <memory>
#include <glm/glm.hpp>

namespace En
{
	class Sprite
	{
	public:
		using TexturePtr = std::shared_ptr<Texture>;
	private:
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		float m_Rotation;
		TexturePtr m_Texture;
		
	public:
		Sprite();
		explicit Sprite(TexturePtr texture, 
						const glm::vec2& pos = { 0,0 }, 
						const glm::vec2& size = { 0,0 }, 
						float rotAngle = 0.0f);

		Sprite(const Sprite& sprite);
		Sprite(Sprite&& sprite) noexcept;
		Sprite& operator=(const Sprite& rhs);
		Sprite& operator=(Sprite&& rhs) noexcept;
	};

}