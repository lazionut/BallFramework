#include "TestGame.h"

namespace BallFramework
{

#define WIDTHUNITS 10
#define HEIGHTUNITS 10

	TestGame::TestGame(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
		: BallGame("Test", width, height, flags, maxFPS)
		/*ballImage{ nullptr },
		ball{ Vector2(0.0f, 0.5f), 2, Vector2::zero, 5 }, rect{ Vector2::zero, 4, 4 },
		color{ 0, 255, 0, 255 }*/ {}

	void TestGame::Start()
	{
		m_ballImage = LoadGameImage("../Assets/ball.png");
		m_ballImages.push_back(m_ballImage);
		if (m_ballImage == nullptr)
		{
			LOGGING_ERROR("Test ball image not found!");
			Stop();
			return;
		}

		m_pickUpImage = LoadGameImage(Paths::ReturnObjectPath("star"));

		m_pickUp.SetActive(true);
		m_pickUp.SetVisible(true);

		m_pickUpGenerator.SetPickUpDefaultProperties(Vector2::right, 1, 5, 5);
		m_pickUpGenerator.SetGeneratorData(GeneratorData(2.0f, 5.0f, 1.0f, 5.0f, 2.0f, 5));

		m_pickUp = m_pickUpGenerator.CreateEmptyPickUp(Vector2::zero);

		m_balls.emplace_back(Ball(Vector2::up, 2, Vector2::up, 0));
		m_pickUp.SetActionType(Actions::BALLSPEEDCHANGE);
		m_pickUpGenerator.SetActions(m_pickUp, &m_balls[0]);

		m_pickUp.InvokeAction();
	}

	void TestGame::OnClose()
	{
		SDL_DestroyTexture(m_ballImage);
		SDL_DestroyTexture(m_pickUpImage);
	}

	void TestGame::CheckCollision()
	{
		//collision
	}

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