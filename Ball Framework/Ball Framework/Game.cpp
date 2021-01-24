#include "Game.h"

namespace BallFramework
{

	Game::Game(const std::string& title, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit)
		: m_maxFPS{ maxFPS }, m_gameEvent{ nullptr }, m_running{ false }, m_renderer{ widthUnit, heightUnit }
	{
		InitGame(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS);
	}

	void Game::InitGame(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	{
		if (m_renderer.InitRenderer(title.c_str(), x, y, width, height, flags))
		{
			m_maxFPS = maxFPS;
			m_gameEvent = std::make_unique<SDL_Event>();
			m_running = true;
		}
	}

	void Game::Run()
	{
		if (m_running)
		{
			Start();
			GameLoop();
			OnClose();
		}
	}

	void Game::Clean()
	{
		LOGGING_WARN("Game cleaned!");
	}

#pragma region PROTECTED METHODS

	void Game::Stop()
	{
		m_running = false;
	}

	[[nodiscard("SDL Texture")]]
	SDL_Texture* Game::LoadGameImage(const std::string& path) const
	{
		return m_renderer.LoadGameImage(path);
	}

	[[nodiscard("SDL Texture")]]
	SDL_Texture* Game::MakeText(const std::string& text, const SDL_Color& fontColor) const
	{
		return m_renderer.MakeText(text, fontColor);
	}

	const ScreenScale& Game::GetScale() const
	{
		return m_renderer.GetScale();
	}

	void Game::SetBackgroundImage(SDL_Texture* backgroundImage)
	{
		m_renderer.SetBackgroundImage(backgroundImage);
	}

	void Game::SetBackgroundColor(const SDL_Color& color)
	{
		m_renderer.SetBackgroundColor(color);
	}

	void Game::SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	{
		const SDL_Color color = { red, green, blue, alpha };
		m_renderer.SetBackgroundColor(color);
	}

	void Game::Repaint()
	{
		m_renderer.ResetRenderer();
		SDL_Renderer* renderer = m_renderer.GetRenderer();

		Render(renderer);
		SDL_RenderPresent(renderer);
	}

#pragma endregion

	void Game::GameLoop()
	{
		double delta = 0;
		double ns;

		int fpsCounter = 0;
		double fpsTimer = 0.0;

		if (m_maxFPS)
		{
			ns = 1.0 / m_maxFPS;
		}
		else
		{
			ns = 0;
		}

		while (m_running)
		{
			m_timeManager.UpdateTime();

			delta += m_timeManager.GetRealDelta();
			fpsTimer += m_timeManager.GetRealDelta();

			if (delta >= ns)
			{
				HandleEvents();

				if (Time::GetTimeScale() > 0)
				{
					Update();
					CheckCollision();
					Repaint();
				}

				m_timeManager.UpdateDone();

				++fpsCounter;
				delta = 0;
			}

			if (fpsTimer >= 1.0)
			{
				LOGGING_TRACE("FPS: {0}", fpsCounter);
				fpsCounter = 0;
				fpsTimer = 0.0;
			}
		}
	}

#pragma region EVENTS
	void Game::HandleEvents()
	{
		while (SDL_PollEvent(m_gameEvent.get()))
		{
			switch (m_gameEvent->type)
			{
			case SDL_QUIT:
				m_running = false;
				return;
			case SDL_KEYDOWN:
				KeyPressed(m_gameEvent->key.keysym.sym);
				break;
			case SDL_KEYUP:
				KeyReleased(m_gameEvent->key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				MousePressed(m_gameEvent->button);
				break;
			case SDL_MOUSEBUTTONUP:
				MouseReleased(m_gameEvent->button);
				break;
			case SDL_WINDOWEVENT:
				HandleWindowEvents(m_gameEvent);
				break;
			default:
				break;
			}
		}
	}

	void Game::HandleWindowEvents(std::unique_ptr<SDL_Event>& gameEvent)
	{
		switch (gameEvent->window.event)
		{
		//case SDL_WINDOWEVENT_SHOWN:
		//	SDL_Log("Window %d shown", gameEvent->window.windowID);
		//	break;
		//case SDL_WINDOWEVENT_HIDDEN:
		//	SDL_Log("Window %d hidden", gameEvent->window.windowID);
		//	break;
		case SDL_WINDOWEVENT_EXPOSED:
			break;
		case SDL_WINDOWEVENT_MOVED:
			m_timeManager.UpdateTime();
			m_timeManager.UpdateDone();
			LOGGING_WARN("Window moved!");
			break;
		case SDL_WINDOWEVENT_RESIZED:
			m_renderer.SetSize(gameEvent->window.data1, gameEvent->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			m_lastTime = Time::GetTimeScale();
			Time::SetTimeScale(0.0f);
			LOGGING_WARN("Window minimized!");
			break;
		case SDL_WINDOWEVENT_RESTORED:
			Time::SetTimeScale(m_lastTime);
			LOGGING_WARN("Window restored!");
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			m_lastTime = Time::GetTimeScale();
			LOGGING_WARN("Window maximazed!");
			break;
		case SDL_WINDOWEVENT_ENTER:
			LOGGING_WARN("Window entered, window id: {0}", gameEvent->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			LOGGING_WARN("Window leave, window id: {0}", gameEvent->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			break;
		case SDL_WINDOWEVENT_CLOSE:
			m_running = false;
			LOGGING_WARN("Window closed!");
			break;
		default:
			LOGGING_WARN("unknown event: {0}", gameEvent->window.event);
			break;
		}
	}
#pragma endregion

	Game::~Game()
	{
		Clean();
	}

}