#include "Timer.h"

void Timer::startTime() { startingTime = SDL_GetTicks(); }

void Timer::updateInstance()
{
	instanceTime++;
}
void Timer::resetInstance()
{
	instanceTime = 0;
}

Uint32 Timer::getInstanceTime() { return instanceTime; }

Uint32 Timer::getStartTime() { return startingTime; }

Uint32 Timer::getDeltaTime() 
{ 
	return SDL_GetTicks() - startingTime; 
};

