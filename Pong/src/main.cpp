#include "Game.h"


int main(int argc, char* argv[])
{
	Game* game = game->instance();

	while (!game->hQuitTitle || !game->hQuitGame)
	{
		if (game->hQuitTitle && game->hQuitGame) { break; }
		if (!game->hQuitTitle || game->hQuitGame) { game->titleScreen(); }
		if (game->hQuitTitle && !game->hQuitGame) 
		{
			game->loadContent();
			game->run();
		}
	}
	

	return 0;
}