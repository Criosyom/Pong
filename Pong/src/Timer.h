#pragma once
#include "SDL.h"
#include <iostream>
class Timer
{
private:
	Uint32 startingTime = 0;
	Uint32 instanceTime = 0;
public:
	void startTime();
	void updateInstance();
	void resetInstance();
	Uint32 getInstanceTime();
	Uint32 getStartTime();
	Uint32 getDeltaTime();
};