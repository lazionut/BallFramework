#include "Colors.h"

namespace BallFramework
{

	const SDL_Color Colors::white = SDL_Color{ 255, 255, 255, 255 };
	const SDL_Color Colors::black = SDL_Color{ 0, 0, 0, 255 };
	const SDL_Color Colors::red = SDL_Color{ 255, 0, 0, 255 };
	const SDL_Color Colors::green = SDL_Color{ 0, 255, 0, 255 };
	const SDL_Color Colors::blue = SDL_Color{ 0, 0, 255, 255 };
	const SDL_Color Colors::dark_green = SDL_Color{ 0, 130, 0, 255 };
	const SDL_Color Colors::dark_blue = SDL_Color{ 0, 0, 130, 255 };
	const SDL_Color Colors::yellow = SDL_Color{ 255, 255, 0, 255 };
	const SDL_Color Colors::orange = SDL_Color{ 255, 130, 0, 255 };
	const SDL_Color Colors::pink = SDL_Color{ 255, 130, 255, 255 };
	const SDL_Color Colors::purple = SDL_Color{ 130, 0, 130, 255 };
	const SDL_Color Colors::violet = SDL_Color{ 255, 0, 255, 255 };
	const SDL_Color Colors::brown = SDL_Color{ 130, 65, 65, 255 };
	const SDL_Color Colors::gray = SDL_Color{ 130, 130, 130, 255 };

	std::unordered_map<std::string, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> Colors::s_CustomColors;

	void Colors::AddCustomColor(std::string colorName, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
	{
		s_CustomColors[colorName] = std::make_tuple(r, g, b, a);
	}

	void Colors::AddCustomColor(std::string colorName, SDL_Color color)
	{
		auto&& [r, g, b, a] = color;
		s_CustomColors[colorName] = std::make_tuple(r, g, b, a);
	}

	bool Colors::RemoveCustomColor(std::string colorName)
	{
		if (s_CustomColors.erase(colorName))
			return true;
		else return false;
	}

	void Colors::ClearCustomColors(std::string colorName)
	{
		s_CustomColors.clear();
	}

	SDL_Color Colors::ReturnCustomColor(std::string colorName)
	{
		if (s_CustomColors.find(colorName) != s_CustomColors.end())
		{
			auto&& [r, g, b, a] = s_CustomColors[colorName];
			return SDL_Color{ r, g, b , a };
		}
		return SDL_Color{ 0,0,0,0 };
	}

	Colors::Colors()
	{
	}

}