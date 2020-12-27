#pragma once
#include"Vector2.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(const Vector2& position, const float& width, const float& height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    void Set(const Vector2& position, float width, float height);
    void Set(float x, float y, float width, float height);

    void SetWidth(float width);
    float GetWidth() const;
    void SetHeight(float height);
    float GetHeight() const;
    void SetPosition(const Vector2& position);
    void SetPosition(float x, float y);
    const Vector2& GetPosition() const;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    friend std::istream& operator>>(std::istream& in, Rectangle& other);
    friend std::ostream& operator<<(std::ostream& out, Rectangle& other);

protected:
    Vector2 m_position;
    float m_width, m_height;
};