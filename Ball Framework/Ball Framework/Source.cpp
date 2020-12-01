#include <iostream>
#include "Pong.h"

int main(int argc, char** argv)
{
	srand(time(0));

	Game* game = new Pong(500, 500, NULL, 60);

	game->Run();

	delete game;

	return 0;
}