#include "GameObject.h"

namespace BallFramework
{

	GameObject::GameObject() noexcept
		: m_position{ Vector2::zero }, m_size{ Vector2::one },
		m_id{ 0 }, m_image{ nullptr } {}

	GameObject::GameObject(const Vector2& position, const Vector2& size, SDL_Texture* image) noexcept
		: m_position{ position }, m_size{ size }, m_image{ image }, m_id{ 0 } {}

	GameObject::GameObject(const Vector2& position, const Vector2& size, const uint16_t id, SDL_Texture* image) noexcept
		: m_position{ position }, m_size{ size }, m_image{ image }, m_id{ id } {}

	uint16_t GameObject::GetId() const noexcept
	{
		return m_id;
	}

	const Vector2& GameObject::GetPosition() const noexcept
	{
		return m_position;
	}

	const Vector2& GameObject::GetSize() const noexcept
	{
		return m_size;
	}

	SDL_Texture* GameObject::GetImage() const noexcept
	{
		return m_image;
	}

	void GameObject::SetId(const uint16_t id) noexcept
	{
		m_id = id;
	}

	void GameObject::SetPosition(const Vector2& position) noexcept
	{
		m_position = position;
	}

	void GameObject::SetSize(const Vector2& size) noexcept
	{
		m_size = size;
	}

	void GameObject::SetImage(SDL_Texture* image) noexcept
	{
		m_image = image;
	}
}
