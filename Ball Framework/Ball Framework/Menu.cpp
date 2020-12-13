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