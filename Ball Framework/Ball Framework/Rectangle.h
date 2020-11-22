#pragma once
#include"Vector2.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(const Vector2& position, const float& width, const float& height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    void Set_Width(const float& width);
    float Get_Width() const;
    void Set_Height(const float& height);
    float Get_Height(const float& height) const;
    void Set_Position(const Vector2& position);
    void Set_Position(const float& x, const float& y);
    Vector2 Get_Position() const;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    friend std::istream& operator>>(std::istream& in, Rectangle& other);
    friend std::ostream& operator<<(std::ostream& out, Rectangle& other);

private:
    Vector2 m_position;
    float m_width, m_height;
};