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

		uint16_t GetId() const noexcept;
		const Vector2& GetPosition() const noexcept;
		const Vector2& GetSize() const noexcept;
		SDL_Texture* GetImage() const noexcept;

		void SetId(const uint16_t id) noexcept;
		void SetPosition(const Vector2& position) noexcept;
		void SetSize(const Vector2& size) noexcept;
		void SetImage(SDL_Texture* image) noexcept;

	protected:
		uint16_t m_id;
		Vector2 m_position;
		Vector2 m_size;
		SDL_Texture* m_image;
	};
}

