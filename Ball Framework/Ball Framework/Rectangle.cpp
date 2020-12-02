#include "Rectangle.h"

Rectangle::Rectangle() :
    m_position{ Vector2::Vector2(0.0f,0.0f) }, m_width{ 0.0f }, m_height{ 0.0f }{
}

Rectangle::Rectangle(const Vector2& position, const float& width, const float& height) :
    m_position{ position }, m_width(width), m_height{ height }{
}

Rectangle::Rectangle(const Rectangle& other)
{
    *this = other;
}

Rectangle::Rectangle(Rectangle&& other) noexcept
{
    *this = std::move(other);
}

void Rectangle::Set(const Vector2& position, float width, float height)
{
    m_position = position;
    m_width = width;
    m_height = height;
}

void Rectangle::Set(float x, float y, float width, float height)
{
    m_position.Set(x, y);
    m_width = width;
    m_height = height;
}

void Rectangle::SetWidth(float width)
{
    m_width = width;
}

float Rectangle::GetWidth() const
{
    return m_width;
}

void Rectangle::SetHeight(float height)
{
    m_height = height;
}

float Rectangle::GetHeight() const
{
    return m_height;
}

void Rectangle::SetPosition(const Vector2& position)
{
    m_position = position;
}

void Rectangle::SetPosition(float x, float y)
{
    m_position.Set(x, y);
}

Vector2 Rectangle::GetPosition() const
{
    return m_position;
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    m_position = other.m_position;
    m_width = other.m_width;
    m_height = other.m_height;
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept
{
    m_position = other.m_position;
    m_width = other.m_width;
    m_height = other.m_height;
    new(&other) Rectangle;
    return *this;
}

std::istream& operator>>(std::istream& in, Rectangle& other)
{
    in >> other.m_position;
    in >> other.m_width;
    in >> other.m_height;
    return in;

}

std::ostream& operator<<(std::ostream& out, Rectangle& other)
{
    out << "Position" << other.m_position;
    out << " Width: " << other.m_width;
    out << " Height: " << other.m_height;
    return out;
}