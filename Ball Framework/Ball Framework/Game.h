#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game
{
public:
    Game();
    Game(const char* title, int x, int y, int width, int height, bool fullscreen);
    Game(const std::string& title, int x, int y, int width, int height, bool fullscreen);

    void initGame(const char* title, int x, int y, int width, int height, bool fullscreen);
    void initGame(const std::string& title, int x, int y, int width, int height, bool fullscreen);
    void run();
    void clean();

protected:

    virtual void start() = 0;
    virtual void checkCollision() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running = false;

    void gameLoop();
    void renderAux();
};

