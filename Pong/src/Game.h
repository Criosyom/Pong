#pragma once
#include "Inputs.h"
#include "Timer.h"
#include "Fonts.h"
#include "Collision.h"
#include <sstream>

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
	Collision* hCollision;

	std::map<std::string, Fonts> Text;

	Texture* texture;
	Inputs inputs;
	std::stringstream fpsCount;
	std::stringstream leftScore;
	std::stringstream rightScore;


	bool hQuit;

	const float FPS = 60.0f;
	int countedFrames;
};