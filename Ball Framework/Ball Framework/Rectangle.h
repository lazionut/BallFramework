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
    void setWidth(const float& width);
    float getWidth() const;
    void setHeight(const float& height);
    float getHeight(const float& height) const;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
};

