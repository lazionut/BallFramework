#pragma once
#include <SDL.h>
#include "Vector2.h"

namespace BallFramework
{

	class GameObject
	{
	public:

		GameObject() noexcept;
		GameObject(const Vector2& position, const Vector2& size, SDL_Texture* image = nullptr) noexcept;
		GameObject(const Vector2& position, const Vector2& size, const uint16_t id, SDL_Texture* image = nullptr) noexcept;

		virtual ~GameObject();

		uint16_t GetId() const noexcept;
		bool IsActive() const noexcept;
		bool IsVisible() const noexcept;
		const Vector2& GetPosition() const noexcept;
		const Vector2& GetSize() const noexcept;
		float GetX() const noexcept;
		float GetY() const noexcept;
		float GetWidth() const noexcept;
		float GetHeight() const noexcept;
		SDL_Texture* GetImage() const noexcept;

		void SetActive(bool active) noexcept;
		void SetVisible(bool visible) noexcept;
		void SetId(const uint16_t id) noexcept;
		void SetPosition(const Vector2& position) noexcept;
		void SetPosition(const float x, const float y) noexcept;
		void SetSize(const Vector2& size) noexcept;
		void SetSize(const float width, const float height) noexcept;
		void SetWidth(const float width) noexcept;
		void SetHeight(const float height) noexcept;
		void SetTransform(const Vector2& position, const Vector2& size) noexcept;
		void SetTransform(const float x, const float y, const float width, const float height) noexcept;
		void SetImage(SDL_Texture* image) noexcept;

	protected:
		bool m_isActive;
		bool m_isVisible;
		uint16_t m_id;
		Vector2 m_position;
		Vector2 m_size;
		SDL_Texture* m_image;
	};

}