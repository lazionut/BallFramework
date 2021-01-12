#pragma once
#include "Game.h"
#include "Pong.h"
#include "BrickBreaker.h"
#include "Button.h"
#include "InfoWindow.h"
#include <vector>
#include <SDL_ttf.h>

namespace BallFramework
{

	class Menu : public Game
	{
	public:
		Menu(int16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

		void InitMenu();
		void LoadFont();

		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Update() override;

		void KeyPressed(const SDL_Keycode& key) override;
		void KeyReleased(const SDL_Keycode& key) override;

		void MousePressed(const SDL_MouseButtonEvent& mouse) override;
		void MouseReleased(const SDL_MouseButtonEvent& mouse) override;

		void Render(SDL_Renderer* renderer) override;

		bool IsInBounds(Sint32 x, Sint32 y);
		void PerformAction();

		void DestroyButtons();

		TTF_Font* GetFont();

	private:
		void InitButtons();

	private:
		std::vector<Button> m_buttons;
		TTF_Font* m_font;
		SDL_Renderer* m_renderer;
		Button* m_lastButton;
	};

}