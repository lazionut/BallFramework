#pragma once
#include <SDL.h>
#include "Rectangle.h"
#include "Time.h"

class Paddle : public Rectangle 
{
public:
	Paddle();
	Paddle(const Vector2& leftDirection, const Vector2& rightDirection, const SDL_Keycode& leftKey,
		const SDL_Keycode& rightKey, const Vector2& leftLimit, const Vector2& rightLimit, float speed);

	void Move();
	void CheckBounds();

	void KeyPressed(const SDL_Keycode& key);
	void KeyReleased(const SDL_Keycode& key);

	float GetSpeed() const;
	void SetSpeed(float speed);
private:
	Vector2 m_direction;
	const Vector2 m_leftDirection, m_rightDirection;
	const SDL_Keycode m_leftKey, m_rightKey;
	const Vector2 m_leftLimit, m_rightLimit;
	float m_speed;
};