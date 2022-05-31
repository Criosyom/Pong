#pragma once
#include "SDL.h"
#include <chrono>
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
	
	/*std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << "Application lifetime: " << duration.count() << " seconds\n";
		std::cout << "Application lifetime: " << SDL_GetTicks() * 0.001 << " seconds\n";

	}*/
};