#include "ScreenScale.h"

ScreenScale::ScreenScale(uint16_t widthUnits, uint16_t heightUnits, uint16_t width, uint16_t height)
	:m_widthUnits{ widthUnits }, m_heightUnits{ heightUnits }, m_width{ width }, m_height{ height }
{
	m_widthUnit = width / m_widthUnits;
	m_heightUnit = height / m_heightUnits;
	m_widthCenter = width / 2;
	m_heightCenter = height / 2;
}

void ScreenScale::Set(uint16_t width, uint16_t height)
{
	m_widthUnit = width / m_widthUnits;
	m_heightUnit = height / m_heightUnits;
	m_widthCenter = width >> 1;
	m_heightCenter = height >> 1;
}

void ScreenScale::PointToPixel(SDL_Rect& rect, float x, float y, float w, float h) const
{
	rect.w = w * m_widthUnit;
	rect.h = h * m_heightUnit;
	rect.x = x * m_widthUnit + m_widthCenter - (rect.w >> 1);
	rect.y = y * -1 * m_heightUnit + m_heightCenter - (rect.h >> 1);
}

void ScreenScale::PointToPixel(SDL_Rect& rect, const Vector2& position, float w, float h) const
{
	rect.w = w * m_widthUnit;
	rect.h = h * m_heightUnit;
	rect.x = position.GetX() * m_widthUnit + m_widthCenter - (rect.w >> 1);
	rect.y = position.GetY() * -1 * m_heightUnit + m_heightCenter - (rect.h >> 1);
}

void ScreenScale::PointToPixel(SDL_Rect& rect, const Vector2& position, const Vector2& size) const
{
	rect.w = size.GetX() * m_widthUnit;
	rect.h = size.GetY() * m_heightUnit;
	rect.x = position.GetX() * m_widthUnit + m_widthCenter - (rect.w >> 1);
	rect.y = position.GetY() * -1 * m_heightUnit + m_heightCenter - (rect.h >> 1);
}