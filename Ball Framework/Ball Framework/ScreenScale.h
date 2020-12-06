#pragma once
#include "Vector2.h"
#include <cstdint>
#include <SDL.H>

class ScreenScale
{
public:
	ScreenScale(uint16_t widthUnits, uint16_t heightUnits, uint16_t width, uint16_t height);

	void Set(uint16_t width, uint16_t height);

	void PointToPixel(SDL_Rect& rect, float x, float y, float w, float h) const;
	void PointToPixel(SDL_Rect& rect, const Vector2& position, const Vector2& size) const;
	void PointToPixel(SDL_Rect& rect, const Vector2& position, float w, float h) const;

	uint16_t GetScreenWidth() const;
	uint16_t GetScreenHeight() const;

private:
	const uint16_t m_widthUnits, m_heightUnits;
	uint16_t m_width, m_height;
	uint16_t m_widthUnit, m_heightUnit;
	uint16_t m_widthCenter, m_heightCenter;
};