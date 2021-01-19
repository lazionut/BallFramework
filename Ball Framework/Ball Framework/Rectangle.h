#pragma once
#include "GameObject.h"

namespace BallFramework
{

	class Rectangle : public GameObject
	{
	public:
		Rectangle() noexcept;
		Rectangle(const Vector2& position, const Vector2& size) noexcept;
		Rectangle(const Vector2& position, const float width, const float height) noexcept;
		Rectangle(const Rectangle& other) noexcept;
		Rectangle(Rectangle&& other) noexcept;

		void Set(const Vector2& position, const Vector2& size) noexcept;
		void Set(const Vector2& position, float width, float height) noexcept;
		void Set(float x, float y, float width, float height) noexcept;

		void SetWidth(float width);
		float GetWidth() const;
		void SetHeight(float height);
		float GetHeight() const;
		void SetPosition(const Vector2& position);
		void SetPosition(float x, float y);
		const Vector2& GetPosition() const;

		void SetSize(float width, float height);
		void SetSize(const Vector2& size);

		void AddSize(const Vector2& size);
		void DecreaseSize(const Vector2& size);

		Rectangle& operator=(const Rectangle& other);
		Rectangle& operator=(Rectangle&& other) noexcept;

		friend std::istream& operator>>(std::istream& in, Rectangle& other);
		friend std::ostream& operator<<(std::ostream& out, Rectangle& other);
	};

}