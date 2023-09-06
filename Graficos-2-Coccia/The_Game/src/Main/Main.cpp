#include <iostream>
#include "..\Game\Game.h"

using namespace Engine;

void main()
{
	Game* game = new Game();

	game->Start();
	game->Play();
	game->End();

	delete game;
}