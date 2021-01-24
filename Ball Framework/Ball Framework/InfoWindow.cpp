#include "InfoWindow.h"

namespace BallFramework
{

	InfoWindow::InfoWindow(const std::string& title, uint16_t width, uint16_t height, uint8_t playersNum,
		uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit) :
		Game(title, width, height, flags, maxFPS, widthUnit, heightUnit),
		m_inputText{ "" },
		m_renderer{ nullptr },
		m_textTexture{ nullptr },
		m_dialogTexture{ nullptr },
		m_width{ width },
		m_height{ height },
		m_validInput{ false },
		m_validName{ false },
		m_playersNumber{ playersNum },
		m_codeValidation{ "[a-z]+[0-9]*" }
	{
	}

	void InfoWindow::Start()
	{
		SDL_StartTextInput();
		if (m_playersNumber == 1)
		{
			m_dialog.SetDialog("");
		}
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
		m_textTexture = MakeText(m_inputText, m_textColor);

		SDL_DestroyTexture(m_dialogTexture);
		m_dialogTexture = MakeText(m_dialog.GetDialog(), m_textColor);

		scale.PointToPixel(rect, Vector2(0.0f, 3.0f), m_dialog.GetDialog().length() / 2, m_height / m_height);
		SDL_RenderCopy(m_renderer, m_dialogTexture, nullptr, &rect);

		scale.PointToPixel(rect, Vector2::zero, m_inputText.length(), m_height / (m_height / 2.5f));
		SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &rect);
	}

	const std::vector<std::string>& InfoWindow::GetPlayersNames() const
	{
		return m_playersNames;
	}

	const bool& InfoWindow::GetValidInput() const
	{
		return m_validInput;
	}

	void InfoWindow::WriteText(const SDL_Keycode& key)
	{
		if (m_inputText.length() < 9
			&& ('a' <= key && key <= 'z') || ('0' <= key && key <= '9'))
		{
			m_inputText += key;

			std::smatch match;
			if (!m_validName && m_inputText.length()>0)
			{
				if (std::regex_match(m_inputText, match, m_codeValidation))
				{
					m_validName = true;
				}
			}
		}
		if (key == SDLK_BACKSPACE && m_inputText.length() > 0)
		{
			m_inputText.pop_back();
		}
		if ((key == SDLK_KP_ENTER || key == SDLK_RETURN) && m_inputText.length() > 0)
		{
			if (m_validName) {
				m_playersNames.emplace_back(m_inputText);
				m_inputText.clear();

				if (m_playersNames.size() < m_playersNumber)
				{
					m_dialog.OtherPlayer();
				}
				m_validName = false;
			}

			if (m_playersNames.size() == m_playersNumber)
			{
				m_validInput = true;
				Stop();
			}
		}
	}

	std::string InfoWindow::Dialog::GetDialog()
	{
		return md_dialog1 + md_currentPlayer + md_dialog2;
	}

	void InfoWindow::Dialog::OtherPlayer()
	{
		md_playerIndex++;
		md_currentPlayer = std::to_string(md_playerIndex);
	}

	void InfoWindow::Dialog::SetDialog(const std::string& text)
	{
		md_currentPlayer = text;
	}

}