#include "Timer.h"

void Timer::startTime() { startingTime = SDL_GetTicks(); }

Uint32 Timer::getStartTime() { return startingTime; }

Uint32 Timer::getDeltaTime() 
{ 
	return SDL_GetTicks() - startingTime; 
};


