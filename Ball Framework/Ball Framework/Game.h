#pragma once
#include <memory>

#include "Renderer.h"
#include "Time.h"
#include "TimeManager.h"

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color black = { 0, 0, 0, 0 };

class Game
{
public:
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
	virtual void MousePressed(const SDL_MouseButtonEvent& mouse) = 0;
	virtual void MouseReleased(const SDL_MouseButtonEvent& mouse) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	[[nodiscard("SDL Texture")]]
	SDL_Texture* LoadImage(const std::string& path) const;

	const ScreenScale& GetScale() const;
	void SetBackgroundColor(const SDL_Color& color);
	void SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	void Stop();
	void Repaint();

private:

	TimeManager m_timeManager;
	Renderer m_renderer;
	std::unique_ptr<SDL_Event> m_gameEvent;
	uint16_t m_maxFPS;
	bool m_running = false;
	
	void GameLoop();

	void HandleEvents();
	void HandleWindowEvents(std::unique_ptr<SDL_Event>& gameEvent);

	void InitGame(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS);
	void Clean();
};