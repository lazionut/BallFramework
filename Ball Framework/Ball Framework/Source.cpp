#include <iostream>
#include "Pong.h"
#include "BrickBreaker.h"

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialized!\n";

		if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		{
			std::cout << "SDL_IMAGE initialized!\n";
			return true;
		}
	}

	return false;
}

int main(int argc, char** argv)
{
	srand(time(0));

	if (initializeSDL())
	{
		Game* game = new Pong(1000, 500, SDL_WINDOW_RESIZABLE, 60);

		game->Run();

		delete game;
	}

	SDL_Quit();

	return 0;
}