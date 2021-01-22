#include "GameObject.h"

namespace BallFramework
{
	GameObject::GameObject() noexcept
		: m_position{ Vector2::zero }, m_size{ Vector2::one },
		m_id{ 0 }, m_image{ nullptr }, m_isActive{ true }, m_isVisible{ true } {}

	GameObject::GameObject(const Vector2& position, const Vector2& size, SDL_Texture* image) noexcept
		: m_position{ position }, m_size{ size }, m_image{ image }, 
		m_id{ 0 }, m_isActive{ true }, m_isVisible{ true } {}

	GameObject::GameObject(const Vector2& position, const Vector2& size, const uint16_t id, SDL_Texture* image) noexcept
		: m_position{ position }, m_size{ size }, m_image{ image }, 
		m_id{ id }, m_isActive{ true }, m_isVisible{ true } {}

	GameObject::~GameObject() {}

	uint16_t GameObject::GetId() const noexcept
	{
		return m_id;
	}

	bool GameObject::IsActive() const noexcept
	{
		return m_isActive;
	}

	bool GameObject::IsVisible() const noexcept
	{
		return m_isVisible && m_isActive;
	}

	const Vector2& GameObject::GetPosition() const noexcept
	{
		return m_position;
	}

	float GameObject::GetX() const noexcept
	{
		return m_position.GetX();
	}

	float GameObject::GetY() const noexcept
	{
		return m_position.GetY();
	}

	const Vector2& GameObject::GetSize() const noexcept
	{
		return m_size;
	}

	float GameObject::GetWidth() const noexcept
	{
		return m_size.GetX();
	}

	float GameObject::GetHeight() const noexcept
	{
		return m_size.GetY();
	}

	SDL_Texture* GameObject::GetImage() const noexcept
	{
		return m_image;
	}

	void GameObject::SetActive(bool active) noexcept
	{
		m_isActive = active;
	}

	void GameObject::SetVisible(bool visible) noexcept
	{
		m_isVisible = visible;
	}

	void GameObject::SetId(const uint16_t id) noexcept
	{
		m_id = id;
	}

	void GameObject::SetPosition(const Vector2& position) noexcept
	{
		m_position = position;
	}

	void GameObject::SetPosition(const float x, const float y) noexcept
	{
		m_position.Set(x, y);
	}

	void GameObject::SetSize(const Vector2& size) noexcept
	{
		m_size = size;
	}

	void GameObject::SetSize(const float width, const float height) noexcept
	{
		m_size.Set(width, height);
	}

	void GameObject::SetWidth(const float width) noexcept
	{
		m_size.SetX(width);
	}

	void GameObject::SetHeight(const float height) noexcept
	{
		m_size.SetY(height);
	}

	void GameObject::SetTransform(const Vector2& position, const Vector2& size) noexcept
	{
		m_position = position;
		m_size = size;
	}

	void GameObject::SetTransform(const float x, const float y, const float width, const float height) noexcept
	{
		m_position.Set(x, y);
		m_size.Set(width, height);
	}

	void GameObject::SetImage(SDL_Texture* image) noexcept
	{
		m_image = image;
	}
}
