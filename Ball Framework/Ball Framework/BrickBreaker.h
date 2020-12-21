#pragma once
#include <SDL_ttf.h>
#include <vector>
#include "PickUpActions.h"
#include "Game.h"
#include "Paddle.h"
#include "Score.h"
#include "Ball.h"
#include "PickUpGenerator.h"
#include "PickUp.h"
#include "PlayersStatistics.h"
#include "Button.h" 

class BrickBreaker : public Game
{
public:
	BrickBreaker(uint16_t width, uint16_t height, TTF_Font* font, uint32_t flags = 0, uint16_t maxFPS = 0);

private:
	void Start() override;
	void OnClose() override;
	void CheckCollision() override;
	void KeyPressed(const SDL_Keycode& key) override;
	void KeyReleased(const SDL_Keycode& key) override;
	void MousePressed(const SDL_MouseButtonEvent& mouse) override;
	void MouseReleased(const SDL_MouseButtonEvent& mouse) override;
	int IsInBounds(Sint32 x, Sint32 y);
	void Render(SDL_Renderer* renderer) override;
	void Update() override;
	void Pause();

	void InitBricks();
	void InitHearts();
	void RenderBricks(SDL_Renderer* renderer);
	void RenderHearts(SDL_Renderer* renderer);
	void CheckPaddleWallCollision();
	void CheckBrickBreakerBallPaddleColision();
	bool CheckBrickBreakerBallWallCollision();
	void CheckBallBricksColision();
	void RenderScore(SDL_Renderer* renderer);
	void ResetBall();
	void CreatePickUp(const Vector2& position);
	void RenderButton(SDL_Renderer* renderer);

	Paddle m_paddle;
	std::vector<std::vector<Rectangle>> m_bricks;
	std::vector<Rectangle> m_hearts;
	Score m_score;
	SDL_Texture* m_ballImage;
	SDL_Texture* m_heartImage;
	SDL_Texture* m_pickUpImage;
	TTF_Font* m_font;
	Ball m_ball;
	PickUp m_pickUp;
	uint16_t m_heartCounter;
	PickUpGenerator m_pickUpGenerator;
	PlayersStatistics playersStatistics;
	Button m_pauseButton;
	float m_lastTimeScale;
	bool m_paused;
	bool m_isPickActive;
	bool m_isPickCreated;
};