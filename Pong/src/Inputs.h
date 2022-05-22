#pragma once
#include "SDL.h"

class Inputs
{
public:
	const Uint8* currentKeyStates;

	Inputs() { currentKeyStates = SDL_GetKeyboardState(NULL); }
	~Inputs() {}

private:
};