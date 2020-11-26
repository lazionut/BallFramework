#include "Game.h"

Game::Game()
    :window{ nullptr }, renderer{ nullptr }, 
    gameEvent{ nullptr }, running{ false }, maxFPS{ 0 } {}

Game::Game(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) 
    : window{ nullptr }, renderer{ nullptr },
    gameEvent{ nullptr }, running { false }
{
    initGame(title, x, y, width, height, fullscreen);
}

Game::Game(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS) 
    : window{ nullptr }, renderer{ nullptr },
    gameEvent{ nullptr }, running{ false }
{
    initGame(title.c_str(), x, y, width, height, fullscreen);
}

void Game::initGame(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS)
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
            this->maxFPS = maxFPS;
            gameEvent = new SDL_Event;
            running = true;
            return;
        }
    }
}

void Game::initGame(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS)
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
    delete gameEvent;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}

void Game::stop()
{
    running = false;
}

void Game::gameLoop()
{
    Time::ResetTime();

    double delta = 0;
    double ns;

    int fpsCounter = 0;
    double fpsTimer = 0.0;

    if (maxFPS)
    {
        ns = 1.0 / maxFPS;
    }
    else
    {
        ns = 0;
    }

    while (running)
    {
        Time::UpdateTime();

        delta += Time::GetRealDelta();
        fpsTimer += Time::GetRealDelta();

        if (delta >= ns)
        {
            handleEvents();
            checkCollision();
            update();
            renderAux();

            Time::UpdateDone();

            ++fpsCounter;
            delta = 0;
        }

        if (fpsTimer >= 1.0)
        {
            std::cout << "FPS: " << fpsCounter << "\n";
            fpsCounter = 0;
            fpsTimer = 0.0;
        }
    }
}

void Game::renderAux()
{
    SDL_RenderClear(renderer);

    render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
    while (SDL_PollEvent(gameEvent))
    {
        if (gameEvent->type == SDL_QUIT)
        {
            running = false;
            return;
        }
    }

    handleInput(SDL_GetKeyboardState(NULL));
}

Game::~Game()
{
    clean();
}
