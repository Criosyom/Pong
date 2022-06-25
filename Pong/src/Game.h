#pragma once
#include "Inputs.h"
#include "AI.h"
#include "TrailEffect.h"

class Game
{
public:
	Game();
	~Game();
	static Game* game;
	static Game* instance();
	void titleScreen();
	void pause();
	void loadContent();
	void run();
	void pauseScreen();
	void release();
	bool hQuitTitle, hQuitGame;

private:
	Graphics* hGraphics;
	SDL_Event hEvents;
	Collision* hCollision;
	AI* hAI; // hello :>
	Texture* texture;
	Inputs inputs;
	Timer timer;
	TrailEffect titleBallTrail, ballTrail, leftPaddleTrail, rightPaddleTrail;

	std::stringstream fpsCount;
	SDL_FRect mid;
	Mix_Chunk* countDown;

	bool titleInitialized, titleTextsLoaded, singlePlayer, ballStarted,
		gameInitialized, gamePaused, gameOver, gameOverTextDisplayed, 
		pauseTextsLoaded, keyReleased, keyReleased2 = true, count3, count2, count1;
	float FPS = 60.0f;
	float frameTicks;
	int countedFrames, oddOrEven;

};