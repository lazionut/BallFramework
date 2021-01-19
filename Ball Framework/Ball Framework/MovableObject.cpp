#include "MovableObject.h"

namespace BallFramework
{
	MovableObject::MovableObject() noexcept
		: GameObject(), m_direction{ Vector2::zero }, m_speed{ 0.0f } {}

	MovableObject::MovableObject(const Vector2& position, const Vector2& size, const Vector2& direction, const float speed, SDL_Texture* image) noexcept
		: GameObject(position, size, image), m_direction{ direction }, m_speed{ speed } {}

	MovableObject::MovableObject(const Vector2& position, const Vector2& size, const Vector2& direction, const float speed, const uint16_t id, SDL_Texture* image) noexcept
		: GameObject(position, size, id, image), m_direction{ direction }, m_speed{ speed } {}

	const Vector2& MovableObject::GetDirection() const noexcept
	{
		return m_direction;
	}

	const float MovableObject::GetSpeed() const noexcept
	{
		return m_speed;
	}

	void MovableObject::SetDirection(const Vector2& direction) noexcept
	{
		m_direction = direction;
	}

	void MovableObject::SetSpeed(const float speed) noexcept
	{
		m_speed = speed;
	}

	void MovableObject::AddSize(const Vector2& size) noexcept
	{
		m_size += size;
	}

	void MovableObject::DecreaseSize(const Vector2& size) noexcept
	{
		m_size -= size;
	}
}