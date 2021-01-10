#include "Colors.h"


//const SDL_Color Colors::white = SDL_Color{ 255, 255, 255, 255 };
//const SDL_Color Colors::black = SDL_Color{ 0, 0, 0, 255 };
//const SDL_Color Colors::red = SDL_Color{ 255, 0, 0, 255 };
//const SDL_Color Colors::green = SDL_Color{ 0, 255, 0, 255 };
//const SDL_Color Colors::blue = SDL_Color{ 0, 0, 255, 255 };
//const SDL_Color Colors::dark_green = SDL_Color{ 0, 130, 0, 255 };
//const SDL_Color Colors::dark_blue = SDL_Color{ 0, 0, 130, 255 };
//const SDL_Color Colors::yellow = SDL_Color{ 255, 255, 0, 255 };
//const SDL_Color Colors::orange = SDL_Color{ 255, 130, 0, 255 };
//const SDL_Color Colors::pink = SDL_Color{ 255, 130, 255, 255 };
//const SDL_Color Colors::purple = SDL_Color{ 130, 0, 130, 255 };
//const SDL_Color Colors::violet = SDL_Color{ 255, 0, 255, 255 };
//const SDL_Color Colors::brown = SDL_Color{ 130, 65, 65, 255 };
//const SDL_Color Colors::gray = SDL_Color{ 130, 130, 130, 255 };

Colors::Colors()
{
}

SDL_Color Colors::ReturnBasicColor(uint8_t color)
{
	switch (color)
	{
	case (0): return SDL_Color{ 255, 255, 255, 255 }; //white
	case (1): return SDL_Color{ 0, 0, 0, 255 }; //black
	case (2): return SDL_Color{ 255, 0, 0, 255 };//red
	case (3): return SDL_Color{ 0, 255, 0, 255 };//gren
	case (4): return SDL_Color{ 0, 0, 255, 255 };//blue
	case (5): return SDL_Color{ 0, 130, 0, 255 };//dark_green
	case (6): return SDL_Color{ 0, 0, 130, 255 };//dark_blue
	case (7): return SDL_Color{ 255, 255, 0, 255 };//yellow
	case (8): return SDL_Color{ 255, 130, 0, 255 };//orange
	case (9): return SDL_Color{ 255, 130, 255, 255 };//pink
	case (10): return SDL_Color{ 130, 0, 130, 255 };//purple
	case (11): return SDL_Color{ 255, 0, 255, 255 };//violet
	case (12): return SDL_Color{ 130, 65, 65, 255 };//brown
	case (13): return SDL_Color{ 130, 130, 130, 255 };//gray

	default:
		SDL_Color{ 0,0,0,0 };
	}
}