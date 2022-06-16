#pragma once
#include "Inputs.h"
#include "AI.h"

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
	void release();

private:
	Graphics* hGraphics;
	SDL_Event hEvents;
	Collision* hCollision;
	AI* hAI; // hello :>
	Texture* texture;
	Inputs inputs;
	Timer timer;

	std::stringstream fpsCount;
	SDL_FRect mid;
	Mix_Chunk* countDown;

	bool hQuitTitle, hQuitGame;
	bool singlePlayer;
	bool soundPlayed3 = false, soundPlayed2 = false, soundPlayed1 = false;
	float FPS = 60.0f;
	float frameTicks;
	int countedFrames;

};