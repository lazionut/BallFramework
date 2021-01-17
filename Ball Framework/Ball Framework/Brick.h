#pragma once
#include <SDL.h>
#include "Rectangle.h"

namespace BallFramework
{

	class Brick : public Rectangle
	{
	public:
		Brick();
		Brick(const Vector2& position, const float width, const float height);
		Brick(const Vector2& position, const float width, const float height, uint16_t m_id, SDL_Color color);
		Brick(const Brick& other);

		uint16_t GetId() const noexcept;
		SDL_Color GetColor() const noexcept;

		void SetId(uint16_t id) noexcept;
		void SetColor(SDL_Color color) noexcept;

	private:
		SDL_Color m_color;
		uint16_t m_id;
	};

}