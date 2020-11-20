#pragma once
#include"Vector2.h"
class Rectangle
{
private:

    Vector2 m_position;
    float m_width, m_height;

public:

    Rectangle();
    Rectangle(const Vector2& position, const float& width, const float& height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
};

