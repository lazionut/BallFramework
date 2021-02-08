#pragma once

#include <SDL_ttf.h>
#include <cstdint>
#include <unordered_map>
#include <tuple>

namespace BallFramework
{

	class Colors
	{
	public:
		// basic color members
		const static SDL_Color white;
		const static SDL_Color black;
		const static SDL_Color red;
		const static SDL_Color green;
		const static SDL_Color blue;
		const static SDL_Color dark_green;
		const static SDL_Color dark_blue;
		const static SDL_Color yellow;
		const static SDL_Color orange;
		const static SDL_Color pink;
		const static SDL_Color purple;
		const static SDL_Color violet;
		const static SDL_Color brown;
		const static SDL_Color gray;

		static void AddCustomColor(std::string colorName, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		static void AddCustomColor(std::string colorName, SDL_Color color);
		static bool RemoveCustomColor(std::string colorName);
		static void ClearCustomColors(std::string colorName);
		static SDL_Color ReturnCustomColor(std::string colorName);

	private:
		Colors();
		static std::unordered_map<std::string, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> s_CustomColors;
	};

}