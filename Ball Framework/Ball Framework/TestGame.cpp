#include "TestGame.h"

namespace BallFramework
{

#define WIDTHUNITS 10
#define HEIGHTUNITS 10

	TestGame::TestGame(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
		: BallGame("Test", width, height, nullptr, flags, maxFPS)
		/*ballImage{ nullptr },
		ball{ Vector2(0.0f, 0.5f), 2, Vector2::zero, 5 }, rect{ Vector2::zero, 4, 4 },
		color{ 0, 255, 0, 255 }*/ {}

	void TestGame::Start()
	{
		m_ballImage = LoadGameImage("../Assets/ball.png");

		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("Test ball image not found!");
			Stop();
			return;
		}

		//SetPaddlesColors({ 255, 255, 255, 255 }, { 255, 0, 0, 255 }, 0.2); nu mai exista setterul

		//nu trebuie neaparat nu emplace back, se poate folosi si push_back
		m_players.emplace_back(Vector2::down, 0.5f, 0.5f, Vector2::zero, Vector2::zero, 0, 0, 0);
		m_balls.emplace_back(Vector2::zero, 1, Vector2::up, 1);


		m_bricks.resize(1);
		SDL_Color color = { 0, 0, 255, 255 };
		for (int i = 0; i < 3; ++i)
		{
			m_bricks[0].emplace_back(Vector2::left * i, 0.5, 0.5, i, color);
		}
	}

	void TestGame::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
	}

	void TestGame::CheckCollision()
	{
		//collision
	}

	/*void TestGame::Update()
	{
		ball.Move();
	}

	void TestGame::KeyPressed(const SDL_Keycode& key)
	{
		switch (key)
		{
		case SDLK_a:
			ball.GetDirection().Set(-1, 0);
			break;
		case SDLK_d:
			ball.GetDirection().Set(1, 0);
			break;
		case SDLK_w:
			ball.GetDirection().Set(0, 1);
			break;
		case SDLK_s:
			ball.GetDirection().Set(0, -1);
			break;
		default:
			break;
		}
	}

	void TestGame::KeyReleased(const SDL_Keycode& key)
	{
		ball.SetDirection(Vector2::zero);
	}*/

	void TestGame::Render(SDL_Renderer* renderer)
	{
		//additional render

		//nu trebuie neaparat in aceasta ordine
		RenderPaddles(renderer);
		RenderGameObjects(renderer);
		RenderBricks(renderer);
		RenderButton(renderer);
		RenderScore(renderer);
	}

	void TestGame::CreatePickUp(const Vector2& position)
	{
		
	}
}