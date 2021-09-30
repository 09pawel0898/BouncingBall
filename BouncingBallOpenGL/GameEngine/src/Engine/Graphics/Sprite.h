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
		TexturePtr m_Texture;
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::vec2 m_GenericSize;
		float m_Rotation;
		glm::vec2 m_Origin = { 0,0 };
	public:
		Sprite();
		explicit Sprite(TexturePtr texture, 
						const glm::vec2& pos = { 0,0 },
						float rotAngle = 0.0f);

		Sprite(const Sprite& sprite);
		Sprite(Sprite&& sprite) noexcept;
		Sprite& operator=(const Sprite& rhs);
		Sprite& operator=(Sprite&& rhs) noexcept;

	private:
		static std::unique_ptr<SpriteRendererData> s_RendererData;
		static std::unique_ptr<SpriteRendererData>& GetRendererData(void) { return s_RendererData; }
		inline void BindTexture(uint8_t texSlot) const { m_Texture->Bind(texSlot); }
		
		friend class Renderer;
	
	public:
		inline void SetTexture(TexturePtr texture)		{ m_Texture = std::move(texture); 
														  SetScale(1.0f); 
														  m_GenericSize = m_Size;}

		inline void SetPosition(const glm::vec2& pos)	{ m_Position = pos; }
		inline glm::vec2 GetPosition(void) const		{ return m_Position; }
		
		inline void SetSize(const glm::vec2& size)		{ m_Size = size;
														  m_GenericSize = m_Size;}

		inline glm::vec2 GetSize(void) const			{ return m_Size; }
		inline glm::vec2 GetGenericSize(void) const		{ return m_GenericSize; }

		inline void SetOrigin(const glm::vec2& origin)	{ m_Origin = origin; }
		inline glm::vec2 GetOrigin(void) const			{ return m_Origin; }

		void SetRotation(float rot);
		inline float GetRotation(void) const			{ return m_Rotation; }
		inline void Rotate(float angle)					{ SetRotation(m_Rotation + angle); }
		
		inline void SetScale(float scale)				{ m_Size = {m_Texture->GetWidth() * scale,	
																	m_Texture->GetHeight() * scale}; }
	};

}