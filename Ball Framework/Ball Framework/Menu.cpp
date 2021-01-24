#include "Menu.h"

namespace BallFramework
{

#define WIDTHUNITS 10
#define HEIGHTUNITS 14
#define MULTIPLAYER 2
#define SINGLEPLAYER 1

	constexpr int buttonsNum = 6;

	Menu::Menu(int16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS) :
		Game("Ball Games", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_buttons{ buttonsNum }, m_lastButton{ nullptr }
	{
	}

	void Menu::Start() 
	{
		InitButtons();
	}

	void Menu::OnClose()
	{
		DestroyButtons();
	}

	void Menu::CheckCollision()
	{
	}

	void Menu::Update()
	{
	}

	void Menu::KeyPressed(const SDL_Keycode& key)
	{
	}

	void Menu::KeyReleased(const SDL_Keycode& key)
	{
	}

	void Menu::MousePressed(const SDL_MouseButtonEvent& mouse)
	{
		if (IsInBounds(mouse.x, mouse.y)) 
		{
			m_lastButton->ChangeBackColor();
		}
	}

	void Menu::MouseReleased(const SDL_MouseButtonEvent& mouse)
	{
		if (m_lastButton != nullptr && IsInBounds(mouse.x, mouse.y)) 
		{
			m_lastButton->ChangeBackColor();
			PerformAction();
		}
	}

	void Menu::Render(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		const auto& scale = GetScale();

		for (auto& button : m_buttons)
		{
			scale.PointToPixel(rect, button.GetPosition(), button.GetWidth(), button.GetHeight());
			SDL_SetRenderDrawColor(renderer, button.GetBackColor().r, button.GetBackColor().g,
				button.GetBackColor().b, button.GetBackColor().a);
			SDL_RenderFillRect(renderer, &rect);
			button.SetRect(rect);

			scale.PointToPixel(rect, button.GetPosition().GetX(), button.GetPosition().GetY(),
				button.GetWidth() - 0.2f, button.GetHeight());

			SDL_RenderCopy(renderer, button.GetText(), nullptr, &rect);
		}
	}

	bool Menu::IsInBounds(Sint32 x, Sint32 y)
	{
		for (auto& button : m_buttons)
		{
			if (x > button.GetRect().x &&
				x < button.GetRect().x + button.GetRect().w &&
				y > button.GetRect().y &&
				y < button.GetRect().y + button.GetRect().h)
			{
				m_lastButton = &button;
				return true;
			}
		}
		return false;
	}

	void Menu::PerformAction()
	{
		std::unique_ptr<InfoWindow> window;
		std::unique_ptr<Game> game;

		switch (m_lastButton->GetButtonId())
		{
		case 0:
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, SINGLEPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<Pong>(1000, 500, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
			break;

		case 1:
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, MULTIPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<PongMP>(1000, 500, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
			break;

		case 2:
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, SINGLEPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<BrickBreaker>(500, 650, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
			break;

		case 3:
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, MULTIPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<BrickBreakerCoop>(500, 650, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
			break;

		case 4:
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, MULTIPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<BrickBreakerVS>(500, 650, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
			break;

		case 5:
			Statistics * stat = new Statistics();
			delete stat;
			break;
		}

		if (game.get())
		{
			game->Run();
		}
	}

	void Menu::DestroyButtons()
	{
		m_buttons.clear();
	}

	void Menu::InitButtons()
	{
		int count = 0;
		float buttonYPos = 5.5f;
		for (auto& button : m_buttons)
		{
			switch (count) {
			case 0:
				button.SetButton(Vector2(0.0f, buttonYPos), 6.0f, 0.7f, Colors::white, Colors::black, "Play Pong Singleplayer", count);
				break;
			case 1:
				button.SetButton(Vector2(0.0f, buttonYPos), 6.0f, 0.7f, Colors::white, Colors::black, "Play Pong Multiplayer", count);
				break;
			case 2:
				button.SetButton(Vector2(0.0f, buttonYPos), 8.0f, 0.7f, Colors::white, Colors::black, "Play BrickBreaker Singleplayer", count);
				break;
			case 3:
				button.SetButton(Vector2(0.0f, buttonYPos), 6.0f, 0.7f, Colors::white, Colors::black, "Play BrickBreaker CO-OP", count);
				break;
			case 4:
				button.SetButton(Vector2(0.0f, buttonYPos), 6.0f, 0.7f, Colors::white, Colors::black, "Play BrickBreaker Versus", count);
				break;
			case 5:
				button.SetButton(Vector2(0.0f, buttonYPos - 1.5f), 3.0f, 0.7f, Colors::white, Colors::black, "Statistics", count);
				break;
			}
			button.SetText(MakeText(button.GetButtonText(), button.GetFontColor()));
			++count;
			buttonYPos -= 1.5f;
		}

	}

}