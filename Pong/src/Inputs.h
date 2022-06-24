#pragma once
#include "Collision.h"

struct Inputs
{
	const Uint8* currentKeyStates;
	SDL_Color PVCColor = { 255, 255, 255 };
	SDL_Color PVPColor = { 255, 255, 255 };
	SDL_Color SPEEDColor = { 255, 255, 255 };
	SDL_Color QuitColor = { 255, 255, 255 };
	SDL_Color ResetColor = { 255, 255, 255 };
	SDL_Color ExitColor = { 255, 255, 255 };
	Inputs();
	~Inputs();
	void titleKeyBoardEvents(SDL_Event* e);
	void keyboardEvents(bool isSingle, bool isGamePaused);
	int mouseEvents(SDL_Event* e);
	int gamePauseEvents(SDL_Event* e);
	int x, y, titleBallWidth = 12, titleBallHeight = 12, titleBallSpeed = 12;
	bool selected, musicSwitched, musicStop = true, pog, pong, eirin = true;
	int titleOptimizer, titleOptimizer2, titleOptimizer3, titleOptimizer4, titleOptimizer5, titleOptimizer6;
	int changeOptimizer, changeOptimizer2, changeOptimizer3, changeOptimizer4;
	Collision* hCollision;
	SDL_Cursor* clickHand;
	SDL_Cursor* arrow;

private:
	Texture* texture;
};