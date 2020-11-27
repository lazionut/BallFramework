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

    ~Game();

protected:

    virtual void start() = 0;
    virtual void checkCollision() = 0;
    virtual void update() = 0;
    virtual void keyPressed(const SDL_Keycode& key) = 0;
    virtual void keyReleased(const SDL_Keycode& key) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

    void stop();

private:
    class TimeManager
    {
    private:
        double deltaTime;
        double realDelta;
        double timeSinceStart;
        double realTime;
        double gameTime;
        double scaledTimeSinceStart;
        double unscaledDelta;

        std::chrono::time_point<std::chrono::system_clock> last;
        std::chrono::time_point<std::chrono::system_clock> now;

        TimeManager(const TimeManager&) = delete;
        TimeManager& operator=(const TimeManager&) = delete;
    public:
        TimeManager();

        void ResetTime();
        void UpdateTime();
        void UpdateDone();

        double GetRealDelta();
    };

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* gameEvent;
    TimeManager timeManager;

    uint16_t maxFPS;
    bool running = false;

    void gameLoop();
    void renderAux();
    void handleEvents();

    void clean();
};