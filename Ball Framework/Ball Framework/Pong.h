#pragma once
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include "ScreenScale.h"
#include "PickUpGenerator.h"
#include "Button.h"
#include <SDL_ttf.h>
#include <vector>

class Pong : public Game
{
public:
	Pong(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void Update() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void MousePressed(const SDL_MouseButtonEvent& mouse) override;
	void MouseReleased(const SDL_MouseButtonEvent& mouse) override;
	int IsInBounds(Sint32 x, Sint32 y);
	void Render(SDL_Renderer* renderer) override;

	void CheckBallWallCollision();
	void CheckPaddleWallCollision();
	void CheckBallPaddleCollision();
	void CheckBallBrickCollision();
	void CheckPickUpCollision();
	void CheckScoreCondition();

	void InitializeBricks();
	void RenderBricks(SDL_Renderer* renderer);
	void RenderPlayersScore(SDL_Renderer* renderer);
	void Pause();
	void ResetBall();
	void CreatePickUp(const Vector2& position);
	void RenderButton(SDL_Renderer* renderer);

	Paddle m_pongPaddle1;
	Paddle m_pongPaddle2;
	std::vector<std::vector<Rectangle>> m_bricks;
	uint16_t m_bricksNumber;

	Ball m_pongBall;
	SDL_Texture* m_ballImage;
	SDL_Renderer* m_renderer;

	TTF_Font* m_font;

	Score m_pongScore1;
	Score m_pongScore2;

	PickUpGenerator m_pickUpGenerator;

	PickUp m_pickUp;
	SDL_Texture* m_pickUpImage;

	Button m_pauseButton;

	float m_lastTimeScale;

	bool m_paused;
	bool m_isPickActive;
	bool m_isPickCreated;
};