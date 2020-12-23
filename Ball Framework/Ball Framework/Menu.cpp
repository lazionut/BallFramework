#include "Menu.h"

#define WIDTHUNITS 10
#define HEIGHTUNITS 10
constexpr int buttonsNum = 2;

Menu::Menu(int16_t width, uint16_t height, uint32_t flags, uint16_t maxFPS) :
	Game("Ball Games", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags, maxFPS, WIDTHUNITS, HEIGHTUNITS),
	m_buttons{ buttonsNum }, m_button{ -1 }
{
	InitMenu();
}


void Menu::InitMenu()
{
	LoadFont();
	InitButtons();
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
	m_button = IsInBounds(mouse.x, mouse.y);
	if (m_button > -1) {
		m_buttons[m_button].ChangeBackColor();
	}
}

void Menu::MouseReleased(const SDL_MouseButtonEvent& mouse)
{
	if (m_button > -1) {
		m_buttons[m_button].ChangeBackColor();
		PerformAction(m_button);
	}
}

void Menu::Render(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	SDL_Rect rect;
	const auto& scale = GetScale();
	SDL_Texture* fontTexture;

	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		scale.PointToPixel(rect, m_buttons[i].GetPosition(), m_buttons[i].GetWidth(), m_buttons[i].GetHeight());
		SDL_SetRenderDrawColor(m_renderer, m_buttons[i].GetBackColor().r, m_buttons[i].GetBackColor().g,
			m_buttons[i].GetBackColor().b, m_buttons[i].GetBackColor().a);
		SDL_RenderFillRect(m_renderer, &rect);
		m_buttons[i].SetRect(rect);

		fontTexture = m_buttons[i].GetText(m_renderer);
		GetScale().PointToPixel(rect, m_buttons[i].GetPosition().GetX(), m_buttons[i].GetPosition().GetY(),
			m_buttons[i].GetWidth() - 0.2f, m_buttons[i].GetHeight());

		if (fontTexture != nullptr)
		{
			SDL_RenderCopy(m_renderer, fontTexture, nullptr, &rect);
			//SDL_DestroyTexture(fontTexture);
		}
	}
}

int Menu::IsInBounds(Sint32 x, Sint32 y)
{
	for (unsigned int i = 0; i < m_buttons.size(); i++) {
		if (x > m_buttons[i].GetRect().x &&
			x < m_buttons[i].GetRect().x + m_buttons[i].GetRect().w
			&& y > m_buttons[i].GetRect().y &&
			y < m_buttons[i].GetRect().y + m_buttons[i].GetRect().h) {
			return i;
		}
	}
	return -1;
}

void Menu::PerformAction(int index)
{
	if (index == 0) {

		Game* pong = new Pong(1000, 500, m_font, SDL_WINDOW_RESIZABLE, 60);
		pong->Run();
		delete pong;
	}
	else {
		Game* brickb = new BrickBreaker(500, 650, m_font, SDL_WINDOW_RESIZABLE, 60);
		brickb->Run();
		delete brickb;
	}
}

void Menu::LoadFont()
{
	m_font = TTF_OpenFont("../Assets/Pixel7.ttf", 24);
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
	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		switch (i) {
		case 0:
			m_buttons[i].SetButton(Vector2(0.0f, 3.0f), 3.0f, 0.7f, white, black, "Play Pong", m_font);
			break;
		case 1:
			m_buttons[i].SetButton(Vector2(0.0f, 1.5f), 5.0f, 0.7f, white, black, "Play BrickBreaker", m_font);
			break;
		}
	}
}