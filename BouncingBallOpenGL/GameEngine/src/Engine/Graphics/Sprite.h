#pragma once

class Texture;

#include <memory>
#include <glm/glm.hpp>

#include "Texture.h"

namespace En
{
	struct SpriteRendererData;

	class Sprite
	{
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

	private:
		static SpriteRendererData s_RendererData;
		static SpriteRendererData& GetRendererData(void) { return s_RendererData; }
		inline void BindTexture(uint8_t texSlot) const { m_Texture->Bind(0); }
		
		friend class Renderer;
	
	public:
		inline void SetPosition(const glm::vec2& pos)	{ m_Position = pos; }
		inline glm::vec2 GetPosition(void) const		{ return m_Position; }
		
		inline void SetSize(const glm::vec2& size)		{ m_Size = size; }
		inline glm::vec2 GetSize(void) const			{ return m_Size; }

		void SetRotation(float rot);
		inline float GetRotation(void) const			{ return m_Rotation; }
		inline void Rotate(float angle)					{ SetRotation(m_Rotation + angle); }
		
		inline void SetScale(float scale)				{ m_Size = {m_Texture->GetWidth() * scale,	
																	m_Texture->GetHeight() * scale}; }
	};

}