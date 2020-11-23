#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
    bool running = false;

    int flags = 0;

    IMG_Init(IMG_INIT_PNG);

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem initialised!\n";
        window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, flags);

        if (window)
        {
            std::cout << "Window created\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!\n";

            int i = 0;
            while (i < INT32_MAX)
            {
                ++i;
            }

            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
        }
    }


	return 0;
}