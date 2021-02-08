#pragma once

#include "BallGame.h"
#include "Rectangle.h"
#include "Ball.h"
#include "Paths.h"
#include "logger.h"
#include "Colors.h"

namespace BallFramework
{

	class TestGame : public BallGame
	{
	public:
		TestGame(uint16_t width, uint16_t height, uint32_t flags = 0, uint16_t maxFPS = 0);

	private:
		void Start() override;
		void OnClose() override;
		void CheckCollision() override;
		void Render(SDL_Renderer* renderer) override;

		void CreatePickUp(const Vector2& position) override;

		/*void Update() override;
		void KeyPressed(const SDL_Keycode& key) override;
		void KeyReleased(const SDL_Keycode& key) override;
		void MousePressed(const SDL_MouseButtonEvent& mouse) override;
		void MouseReleased(const SDL_MouseButtonEvent& mouse) override;*/

		//Ball ball;
		//Rectangle rect;
		//SDL_Texture* ballImage;
		//SDL_Color color;
	};

}