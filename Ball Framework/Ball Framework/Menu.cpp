#include "Menu.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 10

static SDL_Color black = { 0, 0, 0, 0 };

Menu::Menu(int16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS) :
	Game("Ball Games", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS)
	
{
	InitMenu();
}


void Menu::InitMenu()
{
	InitButtons();
	LoadFont();
}

void Menu::Start() {
}

void Menu::OnClose()
{
	//TTF_CloseFont(m_font);
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
}

void Menu::MouseReleased(const SDL_MouseButtonEvent& mouse)
{
}

void Menu::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	const auto& scale = GetScale();
	SDL_Texture* fontTexture;

	for (auto i = 0; i < m_buttons.size(); i++)
	{
		scale.PointToPixel(rect, m_buttons[i].GetPosition(), m_buttons[i].GetWidth(), m_buttons[i].GetHeight());
		SDL_SetRenderDrawColor(renderer, m_buttons[i].GetColor().r, m_buttons[i].GetColor().g,
			m_buttons[i].GetColor().b, m_buttons[i].GetColor().a);
		SDL_RenderFillRect(renderer, &rect);
		m_buttons[i].SetRect(rect);

		fontTexture = m_buttons[i].GetText(renderer, m_font);
		GetScale().PointToPixel(rect, m_buttons[i].GetPosition().GetX(), m_buttons[i].GetPosition().GetY(),
			m_buttons[i].GetWidth() - 0.2f, m_buttons[i].GetHeight());

		if (fontTexture != nullptr)
		{
			SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
			SDL_DestroyTexture(fontTexture);
		}
	}
}


void Menu::LoadFont()
{
	m_font = TTF_OpenFont("Pixel7.ttf", 24);
	if (m_font == NULL) {
		std::cout << "Could not load the font! " << TTF_GetError() << std::endl;
		TTF_CloseFont(m_font);
	}
}

TTF_Font* Menu::GetFont()
{
	return m_font;
}

void Menu::InitButtons()
{
	for (auto i = 0; i < m_buttons.size(); i++)
	{
		switch (i) {
		case 0:
			m_buttons[i].SetButton(Vector2(0.0f, 3.0f), 3.0f, 0.7f, "Play Pong");
			break;
		case 1:
			m_buttons[i].SetButton(Vector2(0.0f, 1.5f), 5.0f, 0.7f, "Play BrickBreaker");
			break;
		}
	}
}