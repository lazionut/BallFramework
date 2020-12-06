#include "Game.h"

Game::Game(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit)
	: m_maxFPS{ maxFPS }, m_gameEvent{ nullptr }, m_running{ false }, m_renderer{ widthUnit, heightUnit }
{
	InitGame(title, x, y, width, height, flags, maxFPS);
}

Game::Game(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit)
	: Game(title.c_str(), x, y, width, height, flags, maxFPS, widthUnit, heightUnit) {}

Game::Game(const char* title, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit)
	: Game(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS, widthUnit, heightUnit) {}

Game::Game(const std::string& title, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS, uint16_t widthUnit, uint16_t heightUnit)
	: Game(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS, widthUnit, heightUnit) {}

void Game::InitGame(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
{
	if (m_renderer.InitRenderer(title, x, y, width, height, flags))
	{
		m_maxFPS = maxFPS;
		m_gameEvent = new SDL_Event;
		m_lastTimeScale = Time::GetTimeScale();
		m_running = true;
	}
}

void Game::InitGame(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
{
	InitGame(title.c_str(), x, y, width, height, flags, maxFPS);
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
	delete m_gameEvent;
	std::cout << "Game cleaned!\n";
}

void Game::Stop()
{
	m_running = false;
}

SDL_Texture* Game::LoadImage(const std::string& path) const
{
	return m_renderer.LoadImage(path);
}

const ScreenScale& Game::GetScale() const
{
	return m_renderer.GetScale();
}

void Game::SetBackgroundColor(const SDL_Color& color)
{
	m_renderer.SetBackgroundColor(color);
}

void Game::SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	SDL_Color color;
	color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
	m_renderer.SetBackgroundColor(color);
}

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

			if (Time::GetTimeScale())
			{
				Update();
				CheckCollision();
				RenderAux();
			}

			m_timeManager.UpdateDone();

			++fpsCounter;
			delta = 0;
		}

		if (fpsTimer >= 1.0)
		{
			std::cout << "FPS: " << fpsCounter << "\n";
			fpsCounter = 0;
			fpsTimer = 0.0;
		}
	}
}

void Game::RenderAux()
{
	SDL_Renderer* renderer = m_renderer.GetRenderer();
	SDL_Color color = m_renderer.GetBackgroundColor();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
	Render(renderer);
	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(m_gameEvent))
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
		case SDL_WINDOWEVENT:
			HandleWindowEvents(m_gameEvent);
			break;
		default:
			break;
		}
	}
}

void Game::HandleWindowEvents(const SDL_Event* gameEvent)
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
		std::cout << "windows moved\n";
		break;
	case SDL_WINDOWEVENT_RESIZED:
		m_renderer.SetSize(gameEvent->window.data1, gameEvent->window.data2);
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		m_lastTimeScale = Time::GetTimeScale();
		Time::SetTimeScale(0.0f);
		break;
	case SDL_WINDOWEVENT_RESTORED:
		Time::SetTimeScale(m_lastTimeScale);
		break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		break;
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		break;
		//case SDL_WINDOWEVENT_CLOSE:
		//	SDL_Log("Window %d closed", gameEvent->window.windowID);
		//	break;
	default:
		break;
	}
}

Game::~Game()
{
	Clean();
}