#pragma once
#include "Inputs.h"
#include "Texture.h"
#include "Timer.h"
#include "Fonts.h"
#include <sstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
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

	Inputs inputs;
	Fonts fonts;
	Fonts fonts2ElectricBoogaloo;
	SDL_Texture* bruh;
	std::stringstream stream;

	bool hQuit;
	
	const int FPS = 60;
	int countedFrames;


};