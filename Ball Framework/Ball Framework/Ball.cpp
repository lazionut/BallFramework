#include "Ball.h"

namespace BallFramework
{

	Ball::Ball()
		: m_position{ Vector2::Vector2(0.0f, 0.0f) }, m_size{ 0.0f }, m_direction(), m_speed(0)
	{
	}

	Ball::Ball(const Vector2& position, float size, const Vector2& direction, float speed)
		: m_position(position), m_size(size), m_direction(direction), m_speed(speed)
	{
	}

	Ball::Ball(const Ball& other)
	{
		*this = other;
	}

	const Vector2& Ball::GetPosition() const
	{
		return m_position;
	}

	Vector2& Ball::GetPosition()
	{
		return m_position;
	}

	float Ball::GetSize() const
	{
		return m_size;
	}

	const Vector2& Ball::GetDirection() const
	{
		return m_direction;
	}

	Vector2& Ball::GetDirection()
	{
		return m_direction;
	}

	float Ball::GetSpeed() const
	{
		return m_speed;
	}

	void Ball::SetPosition(const Vector2& position)
	{
		m_position = position;
	}

	void Ball::SetPosition(float x, float y)
	{
		m_position.Set(x, y);
	}

	void Ball::SetSize(float size)
	{
		m_size = size;
	}

	void Ball::SetDirection(const Vector2& direction)
	{
		m_direction = direction;
	}

	void Ball::SetDirection(float x, float y)
	{
		m_direction.Set(x, y);
	}

	void Ball::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void Ball::AddSpeed(float difference)
	{
		m_speed += difference;
	}

	void Ball::Move()
	{
		m_position += (m_direction * m_speed * Time::GetDeltaTime());
	}

	bool Ball::CheckCollision(const Rectangle& rect)
	{
		float x, y;
		const auto& rectPos = rect.GetPosition();
		float ballx = m_position.GetX(), bally = m_position.GetY();
		float rectWidth = rect.GetWidth();
		float rectHeight = rect.GetHeight();
		float rectx = rectPos.GetX() - rectWidth / 2;
		float recty = rectPos.GetY() - rectHeight / 2;

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

		if (deltaX * deltaX + deltaY * deltaY < (m_size * m_size / 4)) //collision was found
		{
			if (x == ballx && y == bally) //ball closest point coordonates are the ball coordonates
			{
				if (m_position == rectPos) //ball has the same coordonates with the rectangle
				{
					m_position += Vector2::up * (rectHeight / 2 + m_size / 2);
					return true;
				}

				Vector2 temp = m_position - rectPos;
				temp.Normalize();

				m_position += temp;

				return true;
			}

			Vector2 difference{ deltaX, deltaY };
			difference.Normalize();
			difference *= m_size / 2;

			m_position = Vector2(x, y) - difference;

			return true;
		}


		return false;
	}

	bool Ball::CheckCollision(const Ball& ball)
	{
		float addedRadius = (m_size + ball.m_size) / 2;

		float x = ball.m_position.GetX() - m_position.GetX();
		float y = ball.m_position.GetY() - m_position.GetY();

		float distance = x * x + y * y;

		if (distance < addedRadius * addedRadius)
		{
			return true;
		}

		return false;
	}

	void Ball::ChangeDirection(const Rectangle& rect)
	{
		auto xRect = rect.GetPosition().GetX();
		auto yRect = rect.GetPosition().GetY();

		if (m_position.GetY() <= yRect + (rect.GetHeight() / 2) && m_position.GetY() >= yRect - rect.GetHeight() / 2)
		{

			if (m_position.GetX() < xRect && m_direction.GetX() < 0)

				m_position.SetX(m_position.GetX() - m_size);

			else
			{
				if (m_position.GetX() > xRect && m_direction.GetX() > 0)

					m_position.SetX(m_position.GetX() + m_size);

				else
					m_direction.SetX(m_direction.GetX() * (-1));
			}
		}

		else
		{
			if (m_position.GetX() <= xRect + (rect.GetWidth() / 2) && m_position.GetX() >= xRect - (rect.GetWidth() / 2))
			{

				if (m_position.GetY() < yRect && m_direction.GetY() < 0)

					m_position.SetY(m_position.GetY() - m_size);
				else
				{
					if (m_position.GetY() > yRect && m_direction.GetY() > 0)

						m_position.SetY(m_position.GetY() + m_size);
					else
						m_direction.SetY(m_direction.GetY() * (-1));
				}

			}
			else {

				if (m_position.GetY() > yRect)
				{
					if (m_position.GetX() >= xRect)
						m_direction.Set(1, 1);
					else
						m_direction.Set(-1, 1);
				}
				else
				{
					if (m_position.GetX() > xRect)
						m_direction.Set(1, -1);
					else
						m_direction.Set(-1, -1);
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