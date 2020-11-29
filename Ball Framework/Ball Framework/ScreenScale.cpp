#include "ScreenScale.h"

ScreenScale::ScreenScale(const uint16_t& widthUnits, const uint16_t& heightUnits,
	const uint16_t& width, const uint16_t& height)
	:m_widthUnits{ widthUnits }, m_heightUnits{ height }, m_width{ width }, m_height{ height }
{
	m_widthUnit = m_width / m_widthUnits;
	m_heightUnit = m_height / m_heightUnits;
	m_widthCenter = m_width / 2;
	m_heightCenter = m_height / 2;
}

void ScreenScale::PointToPixel(SDL_Rect& rect, float x, float y, float w, float h) const
{
	rect.w = w * m_widthUnit;
	rect.h = h * m_heightUnit;
	rect.x = x * m_widthUnit + m_widthCenter - rect.w / 2;
	rect.y = y * -1 * m_heightUnit + m_heightCenter - rect.h / 2;
}

void ScreenScale::PointToPixel(SDL_Rect& rect, const Vector2& position, const Vector2& size) const
{
	rect.w = size.GetX() * m_widthUnit;
	rect.h = size.GetY() * m_heightUnit;
	rect.x = position.GetX() * m_widthUnit + m_widthCenter - rect.w / 2;
	rect.y = position.GetY() * -1 * m_heightUnit + m_heightCenter - rect.h / 2;
}