#include "Renderer.h"

Renderer::Renderer(uint16_t widthUnits, uint16_t heightUnit)
	: m_renderer{ nullptr }, m_window{ nullptr }, 
	m_scale{ widthUnits, heightUnit,1 ,1 }, m_backgroundColor{ 255, 255, 255, 255 } {}

bool Renderer::InitRenderer(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags)
{
	m_window = SDL_CreateWindow(title, x, y, width, height, flags);

	if (m_window)
	{
		std::cout << "window created!\n";
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);

		if (m_renderer)
		{
			std::cout << "renderer created!\n";
			m_scale.Set(width, height);

			return true;
		}
	}

	return false;
}

SDL_Renderer* Renderer::GetRenderer()
{
	return m_renderer;
}

const ScreenScale& Renderer::GetScale()
{
	return m_scale;
}

const SDL_Color& Renderer::GetBackgroundColor()
{
	return m_backgroundColor;
}

void Renderer::SetBackgroundColor(const SDL_Color& color)
{
	m_backgroundColor = color;
}

void Renderer::SetSize(uint16_t width, uint16_t height)
{
	m_scale.Set(width, height);
}

Renderer::~Renderer()
{
	std::cout << "renderer cleaned!\n";
	Clean();
}

void Renderer::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}
