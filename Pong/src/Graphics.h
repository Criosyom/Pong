#pragma once
#include "SDL.h"
#include <iostream>
class Graphics
{
public:

	Graphics();
	~Graphics();

	void init();
	void clearBuffer();
	void render();

	static Graphics* instance();

	SDL_Renderer* getRenderer() { return hRenderer; }
	SDL_Window* getWindow() { return hWindow; }
	const int getWindowWidth() { return hWindowWidth; }
	const int getWindowHeight() { return hWindowHeight; }

private:

	SDL_Window* hWindow;
	SDL_Renderer* hRenderer;
	SDL_Surface hSurface;

	static Graphics* hInstance;
	static const int hWindowWidth = 858;
	static const int hWindowHeight = 525;
};