#include "Renderer.h"

namespace BallFramework
{

	Renderer::Renderer(uint16_t widthUnits, uint16_t heightUnit) noexcept
		: m_renderer{ nullptr }, m_window{ nullptr }, m_backgroundImage{ nullptr }, m_font{ nullptr },
		m_scale{ widthUnits, heightUnit, 1, 1 }, m_backgroundColor{ 15, 15, 15, 255 } {}

	bool Renderer::InitRenderer(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags) noexcept
	{
		m_window = SDL_CreateWindow(title, x, y, width, height, flags);

		if (m_window)
		{
			LOGGING_WARN("Window created!");
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);

			if (m_renderer)
			{
				LOGGING_WARN("Renderer created!");
				m_scale.Set(width, height);
				if (m_renderer) 
				{
					LoadFont("../Assets/Pixel7.ttf");
					return true;
				}
			}
		}
		return false;
	}

	SDL_Renderer* Renderer::GetRenderer() const noexcept
	{
		return m_renderer;
	}

	const ScreenScale& Renderer::GetScale() const noexcept
	{
		return m_scale;
	}

	const SDL_Color& Renderer::GetBackgroundColor() const noexcept
	{
		return m_backgroundColor;
	}

	const TTF_Font* Renderer::GetFont() const noexcept
	{
		return m_font;
	}

	[[nodiscard("SDL Texture")]]
	SDL_Texture* Renderer::LoadGameImage(const std::string& path) const
	{
		SDL_Surface* loadedImage = IMG_Load(path.c_str());

		if (loadedImage)
		{
			SDL_Texture* result = SDL_CreateTextureFromSurface(m_renderer, loadedImage);
			SDL_FreeSurface(loadedImage);
			return result;
		}

		LOGGING_ERROR("Image not found!");
		return nullptr;
	}

	[[nodiscard("SDL Texture")]]
	SDL_Texture* Renderer::MakeText(const std::string& text, const SDL_Color& fontColor) const
	{
		SDL_Surface* loadedText = TTF_RenderText_Solid(m_font, text.c_str(), fontColor);
		SDL_Texture* sdlText = SDL_CreateTextureFromSurface(m_renderer, loadedText);
		SDL_FreeSurface(loadedText);
		return  sdlText;
	}

	void Renderer::ResetRenderer()
	{
		SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, 
			m_backgroundColor.b, m_backgroundColor.a);
		SDL_RenderClear(m_renderer);

		if (SDL_Texture* image = m_backgroundImage; image != nullptr)
		{
			SDL_Rect rect;
			m_scale.FillScreen(rect);
			SDL_RenderCopy(m_renderer, image, nullptr, &rect);
		}
	}

	void Renderer::SetBackgroundColor(const SDL_Color& color) noexcept
	{
		m_backgroundColor = color;
	}

	void Renderer::SetBackgroundImage(SDL_Texture* backgroundImage) noexcept
	{
		if (m_backgroundImage != nullptr)
		{
			SDL_DestroyTexture(m_backgroundImage);
		}
		m_backgroundImage = backgroundImage;
	}

	void Renderer::SetSize(uint16_t width, uint16_t height) noexcept
	{
		m_scale.Set(width, height);
	}

	Renderer::~Renderer()
	{
		Clean();
	}

	void Renderer::Clean()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_backgroundImage);
		TTF_CloseFont(m_font);

		LOGGING_WARN("Renderer cleaned!");
	}

	void Renderer::LoadFont(std::string path)
	{
		m_font = TTF_OpenFont(path.c_str(), 24);
		if (m_font == nullptr)
		{
			LOGGING_ERROR("Font not found!");
			TTF_CloseFont(m_font);
		}
	}
}