#pragma once
#include "Renderer.h"
#include "Time.h"
#include "TimeManager.h"

class Game
{
public:

	Game(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);
	Game(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);
	Game(const char* title, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);
	Game(const std::string& title, uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);

	void Run();

	virtual ~Game();

protected:

	virtual void Start() = 0;
	virtual void OnClose() = 0;
	virtual void CheckCollision() = 0;
	virtual void Update() = 0;
	virtual void KeyPressed(const SDL_Keycode& key) = 0;
	virtual void KeyReleased(const SDL_Keycode& key) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	SDL_Texture* LoadImage(const std::string& path) const;
	const ScreenScale& GetScale() const;
	void SetBackgroundColor(const SDL_Color& color);
	void SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	void Stop();

private:

	TimeManager m_timeManager;
	Renderer m_renderer;
	SDL_Event* m_gameEvent;
	
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