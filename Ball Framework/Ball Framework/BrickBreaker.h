#pragma once
#include "Game.h"

class BrickBreaker: public Game
{
public:
    BrickBreaker();
    BrickBreaker(const char* title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);
    BrickBreaker(const std::string& title, int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);

private:
    virtual void start() override;
    virtual void checkCollision() override;
    virtual void update() override;
    virtual void keyPressed(const SDL_Keycode& key) override;
    virtual void keyReleased(const SDL_Keycode& key) override;
    virtual void render(SDL_Renderer* renderer) override;

};

