#pragma once
#include "Vector2.h"
#include <cstdint>
#include <SDL.H>

namespace BallFramework
{

	class ScreenScale
	{
	public:
		ScreenScale(uint16_t widthUnits, uint16_t heightUnits, uint16_t width, uint16_t height) noexcept;

		void Set(uint16_t width, uint16_t height) noexcept;

		void PointToPixel(SDL_Rect& rect, float x, float y, float w, float h) const noexcept;
		void PointToPixel(SDL_Rect& rect, const Vector2& position, const Vector2& size) const noexcept;
		void PointToPixel(SDL_Rect& rect, const Vector2& position, float w, float h) const noexcept;
		void FillScreen(SDL_Rect& rect) const noexcept;

		uint16_t GetScreenWidth() const noexcept;
		uint16_t GetScreenHeight() const noexcept;

	private:
		const uint16_t m_widthUnits, m_heightUnits;
		uint16_t m_width, m_height;
		uint16_t m_widthUnit, m_heightUnit;
		uint16_t m_widthCenter, m_heightCenter;
	};

}