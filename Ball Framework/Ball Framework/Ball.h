#pragma once
#include "MovableObject.h"
#include "Rectangle.h"

namespace BallFramework
{

	class Ball : public MovableObject
	{
	public:
		Ball();
		Ball(const Vector2& position, float size, const Vector2& direction, float speed);
		Ball(const Ball& other);

		Vector2& GetPosition();
		Vector2& GetDirection();

		float GetSize() const noexcept;
		void SetSize(float size);

		void ChangeDirection(const GameObject& rect);

		bool CheckCollision(const GameObject& rect);
		bool CheckCollision(const Ball& ball);

		Ball& operator=(const Ball& other);
		Ball& operator=(Ball&& other) noexcept;
	};

}