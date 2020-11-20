#include "Rectangle.h"
Rectangle::Rectangle() :
    m_position{ Vector2::Vector2(0.0,0.0) }, m_width{ 0.0 }, m_height{ 0.0 }
{

}

Rectangle::Rectangle(const Vector2& position, const float& width, const float& height) :
    m_position{ position }, m_width(width), m_height{ height }
{

}

Rectangle::Rectangle(const Rectangle& other)
{
    *this = other;
}

Rectangle::Rectangle(Rectangle&& other) noexcept
{
    *this = std::move(other);
}
void Rectangle::setWidth(const float& width)
{
    m_width = width;
}

float Rectangle::getWidth() const
{
    return m_width;
}

void Rectangle::setHeight(const float& height)
{
    m_height = height;
}

float Rectangle::getHeight(const float& height) const
{
    return m_height;
}
void Rectangle::setPosition(const Vector2& position)
{
    m_position = position;
}

void Rectangle::setPosition(const float& x, const float& y)
{
    m_position.setX(x);
    m_position.setY(y);
}

Vector2 Rectangle::getPosition() const
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