#pragma once
#include "Collision.h"

struct Inputs
{
	const Uint8* currentKeyStates;
	SDL_Color PVCColor = { 255, 255, 255 };
	SDL_Color PVPColor = { 255, 255, 255 };
	SDL_Color SPEEDColor = { 255, 255, 255 };
	SDL_Color ExitColor = { 255, 255, 255 };

	Inputs();
	~Inputs();
	int mouseEvents(SDL_Event* e);
	void keyboardEvents(bool isSingle);
	int x, y;	

	Collision* hCollision;

private:
	Texture* texture;
	bool selected = false;

};

