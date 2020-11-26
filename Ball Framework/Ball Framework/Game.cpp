#include "Game.h"

Game::Game()
    :window { nullptr }, renderer { nullptr }, running { false } {}

Game::Game(const char* title, int x, int y, int width, int height, bool fullscreen) : running { false }
{
    initGame(title, x, y, width, height, fullscreen);
}

Game::Game(const std::string& title, int x, int y, int width, int height, bool fullscreen) : running { false }
{
    initGame(title.c_str(), x, y, width, height, fullscreen);
}

void Game::initGame(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem initialised!\n";
        window = SDL_CreateWindow(title, x, y, width, height, flags);

        if (window)
        {
            std::cout << "Window created\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!\n";
        }

        //scale.setScreenBounds(width, height);

        if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
        {
            running = true;
            return;
        }
    }
}

void Game::initGame(const std::string& title, int x, int y, int width, int height, bool fullscreen)
{
    initGame(title.c_str(), x, y, width, height, fullscreen);
}

void Game::run()
{
    start();
	gameLoop();
    clean();
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}

void Game::gameLoop()
{
    std::cout << "game loop\n";
    checkCollision();
    update();
    renderAux();
}

void Game::renderAux()
{
    SDL_RenderClear(renderer);

    render();

    SDL_RenderPresent(renderer);
}
