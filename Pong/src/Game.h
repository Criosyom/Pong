#pragma once
//#include "Entity.h"
#include "Texture.h"
#include "Graphics.h"

class Game
{
public:

	Game();
	~Game();

	static Game* game;
	static Game* instance();
	void loadContent();
	void run();
	void release();

private:

	SDL_Event hEvents;
	Graphics* hGraphics;

	Texture* playerPaddle;
	Texture* opponentPaddle;
	Texture* middleLine;
	Texture* ball;

	SDL_Rect src, dst;


	bool hQuit;
	
};