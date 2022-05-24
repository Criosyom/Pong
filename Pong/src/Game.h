#pragma once
#include "Inputs.h"
#include "Texture.h"
#include "Timer.h"
#include "Fonts.h"
#include <sstream>
#include <math.h>
#include <map>
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

	std::map<std::string, Texture*> Textures;
	std::map<std::string, Fonts> Text;

	Inputs inputs;
	std::stringstream stream;

	bool hQuit;

	bool q, w, e, r;


	const int FPS = 60;
	int countedFrames;


};