#pragma once
#include "GameObject.h"

namespace BallFramework
{
    class MovableObject : public GameObject
    {
    public:

        MovableObject() noexcept;
        MovableObject(const Vector2& position, const Vector2& size, const Vector2& direction, const float speed, SDL_Texture* image = nullptr) noexcept;
        MovableObject(const Vector2& position, const Vector2& size, const Vector2& direction, const float speed, const uint16_t id, SDL_Texture* image = nullptr) noexcept;

        const Vector2& GetDirection() const noexcept;
        const float GetSpeed() const noexcept;

        void SetDirection(const Vector2& direction) noexcept;
        void SetSpeed(const float speed) noexcept;

        void AddSize(const Vector2& size) noexcept;
        void DecreaseSize(const Vector2& size) noexcept;

    protected:
        Vector2 m_direction;
        float m_speed;
    };
}

