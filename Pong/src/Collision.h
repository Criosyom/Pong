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
	void titleCollisionCheck();
	void ballCollisionCheck(bool isGamePaused);

	int leftPoints = 0, rightPoints = 0;

	Mix_Chunk* paddleSound;
	Mix_Chunk* borderSound;
	Mix_Chunk* scoreSound;
	Mix_Chunk* selectSound;
	bool scored = false;
	std::stringstream leftScore;
	std::stringstream rightScore;
	std::map<std::string, Fonts> Text;
	bool titleTop, titleBottom, titleLeft, titleRight;
	bool bouncedPlayer, bouncedOpponent, bouncedBottom, bouncedBottomCheck, bouncedTop, bouncedTopCheck, touchedLeft, touchedRight, touchedGrass;
	Timer* timer;

private:
	Graphics* graphics;
	Texture* texture;
	static Collision* hInstance;
};