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
		WriteText(key);
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
		SDL_Rect rect;
		const auto& scale = GetScale();

		SDL_DestroyTexture(m_textTexture);
		m_textTexture = MakeText(m_inputText, m_textColor, m_font);

		SDL_DestroyTexture(m_dialogTexture);
		m_dialogTexture = MakeText(m_dialog.GetDialog(), m_textColor, m_font);

		scale.PointToPixel(rect, Vector2(0.0f, 3.0f), m_dialog.GetDialog().length() / 2, m_height / m_height);
		SDL_RenderCopy(m_renderer, m_dialogTexture, nullptr, &rect);

		scale.PointToPixel(rect, Vector2::zero, m_inputText.length(), m_height / (m_height / 2.5f));
		SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &rect);
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

	void InfoWindow::WriteText(const SDL_Keycode& key)
	{
		if (m_inputText.length() < 9
			&& ('a' <= key && key <= 'z') || ('0' <= key && key <= '9'))
		{
			m_inputText += key;
		}
		if (key == SDLK_BACKSPACE && m_inputText.length() > 0)
		{
			m_inputText.pop_back();
		}
		if ((key == SDLK_KP_ENTER || key == SDLK_RETURN) && m_inputText.length() > 0)
		{
			if (m_player1Name.empty()) {
				m_player1Name = m_inputText;
				m_inputText.clear();

				if (m_gameType == false) {
					Stop();
				}
				else {
					m_dialog.OtherPlayer();
				}
				return;
			}
			else if (m_gameType == true) {
				if (!m_player2Name.has_value()) {
					m_player2Name = m_inputText;
					m_inputText.clear();
					Stop();
					return;
				}
			}
		}
	}

	std::string InfoWindow::Dialog::GetDialog()
	{
		return md_dialog1 + md_currentPlayer + md_dialog2;
	}

	void InfoWindow::Dialog::OtherPlayer()
	{
		md_currentPlayer = "2";
	}

}