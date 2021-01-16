#include "Menu.h"

namespace BallFramework
{

#define WIDTHUNITS 10
#define HEIGHTUNITS 10
#define MULTIPLAYER 2
#define SINGLEPLAYER 1

	constexpr int buttonsNum = 2;

	Menu::Menu(int16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS) :
		Game("Ball Games", width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
		m_buttons{ buttonsNum }, m_lastButton{ nullptr }
	{
		InitMenu();
	}

	void Menu::InitMenu()
	{
		LoadFont();
		InitButtons();
	}

	void Menu::Start() 
	{
	}

	void Menu::OnClose()
	{
		TTF_CloseFont(m_font);
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
		m_renderer = renderer;
		SDL_Rect rect;
		const auto& scale = GetScale();

		for (auto& button : m_buttons)
		{
			scale.PointToPixel(rect, button.GetPosition(), button.GetWidth(), button.GetHeight());
			SDL_SetRenderDrawColor(m_renderer, button.GetBackColor().r, button.GetBackColor().g,
				button.GetBackColor().b, button.GetBackColor().a);
			SDL_RenderFillRect(m_renderer, &rect);
			button.SetRect(rect);

			scale.PointToPixel(rect, button.GetPosition().GetX(), button.GetPosition().GetY(),
				button.GetWidth() - 0.2f, button.GetHeight());

			SDL_RenderCopy(m_renderer, button.GetText(), nullptr, &rect);
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

		if (m_lastButton == &m_buttons.at(0))
		{
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, m_font, MULTIPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<PongMP>(1000, 500, m_font, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
		}
		else
		{
			window = std::make_unique<InfoWindow>("Insert Players", 300, 300, m_font, SINGLEPLAYER, SDL_WINDOW_RESIZABLE, 20);
			window->Run();
			if (window->GetValidInput())
			{
				game = std::make_unique<BrickBreaker>(500, 650, m_font, window->GetPlayersNames(), SDL_WINDOW_RESIZABLE, 60);
			}
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

	void Menu::LoadFont()
	{
		m_font = TTF_OpenFont("../Assets/Pixel7.ttf", 24);
		if (m_font == nullptr)
		{
			LOGGING_ERROR("Menu font not found!");
			TTF_CloseFont(m_font);
		}
	}

	TTF_Font* Menu::GetFont()
	{
		return m_font;
	}

	void Menu::InitButtons()
	{
		int count = 0;
		for (auto& button : m_buttons)
		{
			if (count == 0) 
			{
				button.SetButton(Vector2(0.0f, 3.0f), 3.0f, 0.7f, Colors::white, Colors::black, "Play Pong");
				button.SetText(MakeText(button.GetButtonText(), button.GetFontColor(), m_font));
			}
			else 
			{
				button.SetButton(Vector2(0.0f, 1.5f), 5.0f, 0.7f, Colors::white, Colors::black, "Play BrickBreaker");
				button.SetText(MakeText(button.GetButtonText(), button.GetFontColor(), m_font));
			}
			++count;
		}
	}

}