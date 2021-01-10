#pragma once
#include <SDL_ttf.h>
#include <cstdint>
#include <unordered_map>
#include <tuple>

class Colors
{
public:

	static enum class BasicColors
	{
		white,
		black,
		red,
		green,
		blue,
		dark_green,
		dark_blue,
		yellow,
		orange,
		pink,
		purple,
		violet,
		brown,
		gray
	};

	static SDL_Color ReturnBasicColor(uint8_t color);

	// basic color members

	/* const static SDL_Color white;
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
	 const static SDL_Color gray;*/

	static std::unordered_map<std::string, std::tuple<uint8_t, uint8_t, uint8_t>> CustomColors;

	static void AddCustomColor(std::string colorName, uint8_t r, uint8_t g, uint8_t b);
	static bool RemoveCustomColor(std::string colorName);
	static void ClearCustomColor(std::string colorName);

	static SDL_Color ReturnCustomColor(std::string colorName);
private:
	Colors();
};
