#include "Rectangle.h"

namespace BallFramework
{

	Rectangle::Rectangle() noexcept
		: GameObject() {}

	Rectangle::Rectangle(const Vector2& position, const Vector2& size) noexcept
		: GameObject(position, size) {}

	Rectangle::Rectangle(const Vector2& position, const float width, const float height) noexcept
		: GameObject(position, Vector2(width, height)) {}

	Rectangle::Rectangle(const Rectangle& other) noexcept
	{
		*this = other;
	}

	Rectangle::Rectangle(Rectangle&& other) noexcept
	{
		*this = std::move(other);
	}

	void Rectangle::Set(const Vector2& position, const Vector2& size) noexcept
	{
		m_position = position;
		m_size = size;
	}

	void Rectangle::Set(const Vector2& position, float width, float height) noexcept
	{
		m_position = position;
		m_size.Set(width, height);
	}

	void Rectangle::Set(float x, float y, float width, float height) noexcept
	{
		m_position.Set(x, y);
		m_size.Set(width, height);
	}

	void Rectangle::SetWidth(float width)
	{
		m_size.SetX(width);
	}

	float Rectangle::GetWidth() const
	{
		return m_size.GetX();
	}

	void Rectangle::SetHeight(float height)
	{
		m_size.SetY(height);
	}

	float Rectangle::GetHeight() const
	{
		return m_size.GetY();
	}

	void Rectangle::SetPosition(const Vector2& position)
	{
		m_position = position;
	}

	void Rectangle::SetPosition(float x, float y)
	{
		m_position.Set(x, y);
	}

	const Vector2& Rectangle::GetPosition() const
	{
		return m_position;
	}

	void Rectangle::SetSize(float width, float height)
	{
		m_size.Set(width, height);
	}

	void Rectangle::SetSize(const Vector2& size)
	{
		m_size = size;
	}

	void Rectangle::AddSize(const Vector2& size)
	{
		m_size += size;
	}

	void Rectangle::DecreaseSize(const Vector2& size)
	{
		m_size -= size;
	}

	Rectangle& Rectangle::operator=(const Rectangle& other)
	{
		m_position = other.m_position;
		m_size = other.m_size;
		return *this;
	}

	Rectangle& Rectangle::operator=(Rectangle&& other) noexcept
	{
		m_position = other.m_position;
		m_size = other.m_size;
		new(&other) Rectangle;
		return *this;
	}

	std::istream& operator>>(std::istream& in, Rectangle& other)
	{
		in >> other.m_position;
		in >> other.m_size;
		return in;
	}

	std::ostream& operator<<(std::ostream& out, Rectangle& other)
	{
		out << "Position" << other.m_position;
		out << " Width: " << other.m_size.GetX();
		out << " Height: " << other.m_size.GetY();
		return out;
	}

}