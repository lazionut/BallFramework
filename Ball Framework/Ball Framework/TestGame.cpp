#include "TestGame.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 10

TestGame::TestGame(uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game("Test", width, height, flags, maxFPS), ballImage{ nullptr },
	ball{ Vector2(-3, 0), 2, Vector2::zero, 5 }, rect{ Vector2::zero, 4, 4 },
	color {0, 255, 0, 255}
{
}

void TestGame::Start()
{
	ballImage = LoadImage("ball.png");

	if (ballImage == nullptr)
	{
		std::cout << "Could not load ball image!\n";
		Stop();
		return;
	}

	color = { 0, 255, 0, 255 };
}

void TestGame::OnClose()
{
	SDL_DestroyTexture(ballImage);
}

void TestGame::CheckCollision()
{
	if (ball.CheckCollision(rect))
	{
		color = { 255, 0, 0, 255 };
	}
	else
	{
		color = { 0, 255, 0, 255 };
	}
}

void TestGame::Update()
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
}

void TestGame::Render(SDL_Renderer* renderer)
{
	SDL_Rect aux;

	const auto& scale = GetScale();

	scale.PointToPixel(aux, rect.GetPosition(), rect.GetWidth(), rect.GetHeight());
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &aux);

	scale.PointToPixel(aux, ball.GetPosition(), ball.GetSize(), ball.GetSize());

	SDL_RenderCopy(renderer, ballImage, nullptr, &aux);

}
