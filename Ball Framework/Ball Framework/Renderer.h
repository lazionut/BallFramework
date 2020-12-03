#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ScreenScale.h"

class Renderer
{
public:
	Renderer(uint16_t widthUnits, uint16_t heightUnit);

	bool InitRenderer(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags);

	SDL_Renderer* GetRenderer() const;
	const ScreenScale& GetScale() const;
	const SDL_Color& GetBackgroundColor() const;

	SDL_Texture* LoadImage(const std::string& path) const;

	void SetBackgroundColor(const SDL_Color& color);
	void SetSize(uint16_t width, uint16_t height);

	~Renderer();
private:

	void Clean();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	ScreenScale m_scale;
	SDL_Color m_backgroundColor;
};

