#pragma once
#include <SDL.h>
#include "Rectangle.h"

namespace BallFramework
{

	class Paddle : public MovableObject
	{
	public:
		Paddle() noexcept;
		Paddle(const Vector2& position, const float& width, const float& height, const Vector2& leftDirection, const Vector2& rightDirection,
			const SDL_Keycode& leftKey, const SDL_Keycode& rightKey, float speed) noexcept;

		void KeyPressed(const SDL_Keycode& key);
		void KeyReleased(const SDL_Keycode& key);

	private:
		const Vector2 m_leftDirection, m_rightDirection;
		const SDL_Keycode m_leftKey, m_rightKey;
		bool m_leftPressed, m_rightPressed;
	};

}