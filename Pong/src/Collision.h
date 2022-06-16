#pragma once
#include "Texture.h"
#include "Timer.h"
#include "Fonts.h"
#include <sstream>
#include <SDL_mixer.h>
#include <ctime>
class Collision
{
public:
	Collision();
	~Collision();
	static Collision* instance();
	void ballCollisionCheck();

	int leftPoints = 0, rightPoints = 0;

	Mix_Chunk* paddleSound;
	Mix_Chunk* borderSound;
	Mix_Chunk* scoreSound;
	Mix_Chunk* selectSound;
	bool scored = false;
	std::stringstream leftScore;
	std::stringstream rightScore;
	std::map<std::string, Fonts> Text;

private:

	bool bouncedPlayer, bouncedOpponent, bouncedBottom, bouncedTop, touchedLeft, touchedRight;
	Graphics* graphics;
	Texture* texture;
	Timer* timer;
	static Collision* hInstance;
};