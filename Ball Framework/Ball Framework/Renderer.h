#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ScreenScale.h"
#include <SDL_TTF.h>
#include "../LoggerDLL/Logger.h"

namespace BallFramework
{

	class Renderer
	{
	public:
		Renderer(uint16_t widthUnits, uint16_t heightUnit) noexcept;

		bool InitRenderer(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags) noexcept;

		SDL_Renderer* GetRenderer() const noexcept;
		SDL_Texture* GetBackgroundImage() const noexcept;
		const ScreenScale& GetScale() const noexcept;
		const SDL_Color& GetBackgroundColor() const noexcept;

		[[nodiscard("SDL Texture")]]
		SDL_Texture* LoadGameImage(const std::string& path) const;
		[[nodiscard("SDL Texture")]]
		SDL_Texture* MakeText(const std::string& text, const SDL_Color& fontColor, TTF_Font* font) const;

		void SetBackgroundColor(const SDL_Color& color) noexcept;
		void SetBackgroundImage(SDL_Texture* backgroundImage) noexcept;
		void SetSize(uint16_t width, uint16_t height) noexcept;

		~Renderer();

	private:
		void Clean();

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_backgroundImage;
		ScreenScale m_scale;
		SDL_Color m_backgroundColor;
	};

}