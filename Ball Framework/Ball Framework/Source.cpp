//#define SDL_MAIN_HANDLED

#include <iostream>
#include "Pong.h"
#include "BrickBreaker.h"
#include "Menu.h"
#include "TestGame.h"

using namespace BallFramework;

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		LOGGING_WARN("Subsystem initialized!");

		if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		{
			LOGGING_WARN("SDL_image initialized!");

			if (TTF_Init() == 0)
			{
				LOGGING_WARN("TTF initialized!");
				return true;
			}
		}
	}

	return false;
}

int main(int argc, char** argv)
{
	Logger::Initialize();

	Paths::SetFilePath("../Assets/assetsPaths.txt");

	srand(time(nullptr));

	if (initializeSDL())
	{
		std::unique_ptr<Game> menu { new Menu(500, 700, SDL_WINDOW_RESIZABLE, 60) };

		menu->Run();
	}

	SDL_Quit();
	TTF_Quit();

	return 0;
}