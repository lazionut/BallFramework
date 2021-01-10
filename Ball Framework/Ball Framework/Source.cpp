//#define SDL_MAIN_HANDLED

#include <iostream>
#include "Pong.h"
#include "BrickBreaker.h"
#include "Menu.h"
#include "TestGame.h"
#include "../LoggerDLL/Logger.h"

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialized!\n";

		if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		{
			std::cout << "SDL_IMAGE initialized!\n";

			if (TTF_Init() == 0)
			{
				std::cout << "TTF initialized!\n";
				return true;
			}
		}
	}

	return false;
}

int main(int argc, char** argv)
{
	Paths::SetFilePath("../Assets/assetsPaths.txt");

	Logger::Initialize();
	INFO("System was initialized!");

	srand(time(0));

	if (initializeSDL())
	{
		Game* menu = new Menu(500, 500, SDL_WINDOW_RESIZABLE, 20);

		menu->Run();

		delete menu;
	}

	SDL_Quit();
	TTF_Quit();

	return 0;
}