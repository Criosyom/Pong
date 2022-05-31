#pragma once
#include "Texture.h"
#include "Timer.h"
#include <ctime>
class Collision
{
public:
	static Collision* instance();
	void ballCollisionCheck();

	int leftPoints = 0, rightPoints = 0;
private:

	bool bouncedPlayer, bouncedOpponent, bouncedBottom, bouncedTop, touchedLeft, touchedRight;

	Graphics* graphics;
	Texture* texture;
	Timer* timer;
	static Collision* hInstance;
	Collision();
	~Collision();

};