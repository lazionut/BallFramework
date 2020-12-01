#pragma once
#include <SDL_image.h>
#include <iostream>
#include "ScreenScale.h"
#include "Time.h"
#include "TimeManager.h"

class Game
{
public:
	Game(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);
	Game(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);
	Game(const char* title, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);
	Game(const std::string& title, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

	void Run();

	virtual ~Game();

protected:

	ScreenScale scale;

	virtual void Start() = 0;
	virtual void OnClose() = 0;
	virtual void CheckCollision() = 0;
	virtual void Update() = 0;
	virtual void KeyPressed(const SDL_Keycode& key) = 0;
	virtual void KeyReleased(const SDL_Keycode& key) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	void Stop();

private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event* m_gameEvent;
	TimeManager m_timeManager;

	uint16_t m_maxFPS;
	bool m_running = false;
	float m_lastTimeScale;

	void GameLoop();
	void RenderAux();
	void HandleEvents();
	void HandleWindowEvents(const SDL_Event* gameEvent);

	void InitGame(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS);
	void InitGame(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS);
	void Clean();
};