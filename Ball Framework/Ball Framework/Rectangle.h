#pragma once
#include"Vector2.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(const Vector2& position, const float& width, const float& height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    void SetWidth(const float& width);
    float GetWidth() const;
    void SetHeight(const float& height);
    float GetHeight(const float& height) const;
    void SetPosition(const Vector2& position);
    void SetPosition(const float& x, const float& y);
    Vector2 GetPosition() const;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    friend std::istream& operator>>(std::istream& in, Rectangle& other);
    friend std::ostream& operator<<(std::ostream& out, Rectangle& other);

private:
    Vector2 m_position;
    float m_width, m_height;
};