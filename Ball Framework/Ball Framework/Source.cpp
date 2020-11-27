#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Pong.h"

int main(int argc, char** argv)
{
	//exemplu main
	Game* game = new Pong("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, false);
	
	game->run();
	
	delete game;

	return 0;
}