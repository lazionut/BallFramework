#pragma once
#include "Game.h"

class BrickBreaker: public Game
{
public:
    BrickBreaker();
    BrickBreaker( int x, int y, int width, int height, bool fullscreen, uint16_t maxFPS = 0);

private:
    void start() override;
    void checkCollision() override;
    void keyPressed(const SDL_Keycode& key) override;
    void keyReleased(const SDL_Keycode& key) override;
    void render(SDL_Renderer* renderer) override;
    void update() override;

};

