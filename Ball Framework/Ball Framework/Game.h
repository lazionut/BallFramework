#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Time.h"

class Game
{
public:
    Game();
    Game(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);
    Game(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);

    void initGame(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);
    void initGame(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);
    void run();

protected:

    virtual void start() = 0;
    virtual void checkCollision() = 0;
    virtual void update() = 0;
    virtual void handleInput(const uint8_t* keyStates) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

    void stop();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* gameEvent;

    uint16_t maxFPS;
    bool running = false;

    void gameLoop();
    void renderAux();
    void handleEvents();

    void clean();

    ~Game();
};

