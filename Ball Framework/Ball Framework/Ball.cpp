#include "Ball.h"
#include <SDL_ttf.h>
namespace BallFramework
{

	Ball::Ball() : MovableObject() {}

	Ball::Ball(const Vector2& position, float size, const Vector2& direction, float speed)
		: MovableObject(position, Vector2(size, size), direction, speed) {}

	Ball::Ball(const Ball& other)
	{
		*this = other;
	}

	Vector2& Ball::GetPosition()
	{
		return m_position;
	}

	Vector2& Ball::GetDirection()
	{
		return m_direction;
	}

	float Ball::GetSize() const noexcept
	{
		return m_size.GetX();
	}

	void Ball::SetSize(float size)
	{
		m_size.Set(size, size);
	}

	bool Ball::CheckCollision(const GameObject& rect)
	{
		float x, y;
		const auto& rectPos = rect.GetPosition();
		float ballx = m_position.GetX(), bally = m_position.GetY();
		float rectWidth = rect.GetWidth();
		float rectHeight = rect.GetHeight();
		float rectx = rectPos.GetX() - rectWidth / 2;
		float recty = rectPos.GetY() - rectHeight / 2;
		float size = GetSize();

		//find the closest x between ball and rectangle
		if (ballx < rectx)
		{
			x = rectx;
		}
		else if (ballx > rectx + rectWidth)
		{
			x = rectx + rectWidth;
		}
		else
		{
			x = ballx;
		}

		//find the closest y between ball and rectangle
		if (bally < recty)
		{
			y = recty;
		}
		else if (bally > recty + rectHeight)
		{
			y = recty + rectHeight;
		}
		else
		{
			y = bally;
		}

		float deltaX = x - ballx;
		float deltaY = y - bally;

		if (deltaX * deltaX + deltaY * deltaY < (size * size / 4)) //collision was found
		{
			if (x == ballx && y == bally) //ball closest point coordonates are the ball coordonates
			{
				if (m_position == rectPos) //ball has the same coordonates with the rectangle
				{
					m_position += Vector2::up * (rectHeight / 2 + size / 2);
					return true;
				}

				Vector2 temp = m_position - rectPos;
				temp.Normalize();

				m_position += temp;

				return true;
			}

			Vector2 difference{ deltaX, deltaY };
			difference.Normalize();
			difference *= size / 2;

			m_position = Vector2(x, y) - difference;

			return true;
		}

		return false;
	}

	bool Ball::CheckCollision(const Ball& ball)
	{

		float addedRadius = (GetSize() + ball.GetSize()) / 2;

		float x = ball.m_position.GetX() - m_position.GetX();
		float y = ball.m_position.GetY() - m_position.GetY();

		float distance = x * x + y * y;

		if (distance < addedRadius * addedRadius)
		{
			return true;
		}

		return false;
	}

	void Ball::ChangeDirection(const GameObject& rect)
	{
		auto xRect = rect.GetPosition().GetX();
		auto yRect = rect.GetPosition().GetY();

		if (m_position.GetY() <= yRect + (rect.GetHeight() / 2) && m_position.GetY() >= yRect - rect.GetHeight() / 2)
		{
			if (m_position.GetX() < xRect && m_direction.GetX() < 0)
			{
				m_position.SetX(m_position.GetX() - GetSize());
			}
			else
			{
				if (m_position.GetX() > xRect && m_direction.GetX() > 0)
				{
					m_position.SetX(m_position.GetX() + GetSize());
				}
				else
				{
					m_direction.SetX(m_direction.GetX() * (-1));
				}
			}
		}
		else
		{
			if (m_position.GetX() <= xRect + (rect.GetWidth() / 2) && m_position.GetX() >= xRect - (rect.GetWidth() / 2))
			{
				if (m_position.GetY() < yRect && m_direction.GetY() < 0)
				{
					m_position.SetY(m_position.GetY() - GetSize());
				}
				else
				{
					if (m_position.GetY() > yRect && m_direction.GetY() > 0)
					{
						m_position.SetY(m_position.GetY() + GetSize());
					}
					else
					{
						m_direction.SetY(m_direction.GetY() * (-1));
					}
				}
			}
			else
			{
				if (m_position.GetY() > yRect)
				{
					if (m_position.GetX() >= xRect)
					{
						m_direction.Set(1, 1);
					}
					else
					{
						m_direction.Set(-1, 1);
					}
				}
				else
				{
					if (m_position.GetX() > xRect)
					{
						m_direction.Set(1, -1);
					}
					else
					{
						m_direction.Set(-1, -1);
					}
				}
			}
		}

		m_direction.Normalize();
	}

	Ball& Ball::operator=(const Ball& other)
	{
		m_position = other.m_position;
		m_size = other.m_size;
		m_direction = other.m_direction;
		m_speed = other.m_speed;
		return *this;
	}

	Ball& Ball::operator=(Ball&& other) noexcept
	{
		m_position = other.m_position;
		m_size = other.m_size;
		m_direction = other.m_direction;
		m_speed = other.m_speed;
		new(&other)Ball;
		return *this;
	}

}