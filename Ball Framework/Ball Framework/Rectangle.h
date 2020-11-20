#pragma once
#include"Vector2.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(const Vector2& position, const float& width, const float& height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    void setWidth(const float& width);
    float getWidth() const;
    void setHeight(const float& height);
    float getHeight(const float& height) const;
    void setPosition(const Vector2& position);
    void setPosition(const float& x, const float& y);
    Vector2 getPosition() const;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    friend std::istream& operator>>(std::istream& in, Rectangle& other);
    friend std::ostream& operator<<(std::ostream& out, Rectangle& other);

private:
    Vector2 m_position;
    float m_width, m_height;
};