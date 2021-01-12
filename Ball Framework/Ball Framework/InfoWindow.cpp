#include "InfoWindow.h"

namespace BallFramework
{

	InfoWindow::InfoWindow(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, bool gameType,
		uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit) :
		Game(title, width, height, flags, maxFPS, widthUnit, heightUnit),
		
		m_font{ font },
		m_renderer{ nullptr },
		m_width{ width },
		m_height{ height },
		m_gameType{ gameType }
	{
	}

	void InfoWindow::Start()
	{
		SDL_StartTextInput();
	}

	void InfoWindow::OnClose()
	{
		SDL_StopTextInput();
	}

	void InfoWindow::CheckCollision()
	{
	}

	void InfoWindow::Update()
	{
	}

	void InfoWindow::KeyPressed(const SDL_Keycode& key)
	{
		
	}

	void InfoWindow::KeyReleased(const SDL_Keycode& key)
	{
	}

	void InfoWindow::MousePressed(const SDL_MouseButtonEvent& mouse)
	{
	}

	void InfoWindow::MouseReleased(const SDL_MouseButtonEvent& mouse)
	{
	}

	void InfoWindow::Render(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
	}

	std::string InfoWindow::GetPlayer1Name() const
	{
		return m_player1Name;
	}

	const std::string& InfoWindow::GetPlayer2Name() const
	{
		if (m_player2Name.has_value()) {
			return m_player2Name.value();
		}
		return "";
	}

}