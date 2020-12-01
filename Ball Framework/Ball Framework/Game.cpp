#include "Game.h"

Game::Game(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: m_window{ nullptr }, m_renderer{ nullptr }, m_maxFPS{ maxFPS },
	m_gameEvent{ nullptr }, m_running{ false }, scale{ 10, 10, width, height }
{
	InitGame(title, x, y, width, height, flags, maxFPS);
}

Game::Game(const std::string& title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: m_window{ nullptr }, m_renderer{ nullptr }, m_maxFPS{ maxFPS },
	m_gameEvent{ nullptr }, m_running{ false }, scale{ 10, 10, width, height }
{
	InitGame(title.c_str(), x, y, width, height, flags, maxFPS);
}

Game::Game(const char* title, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS) {}

Game::Game(const std::string& title, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
	: Game(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS) {}

void Game::InitGame(const char* title, int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialised!\n";
		m_window = SDL_CreateWindow(title, x, y, width, height, flags);

		if (m_window)
		{
			std::cout << "Window created\n";

			m_renderer = SDL_CreateRenderer(m_window, -1, 0);

			if (m_renderer)
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
				std::cout << "Renderer created!\n";

				if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
				{
					std::cout << "SDL_IMAGE initialized!\n";

					m_maxFPS = maxFPS;
					m_gameEvent = new SDL_Event;
					m_running = true;
					m_lastTimeScale = Time::GetTimeScale();
					return;
				}
			}
		}
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
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Game cleaned!\n";
}

void Game::Stop()
{
	m_running = false;
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
			CheckCollision();
			Update();
			RenderAux();

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
	SDL_RenderClear(m_renderer);

	Render(m_renderer);

	SDL_RenderPresent(m_renderer);
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
		break;
	case SDL_WINDOWEVENT_RESIZED:
		//SDL_Log("Window %d resized to %dx%d",
		//	gameEvent->window.windowID, gameEvent->window.data1,
		//	gameEvent->window.data2);
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