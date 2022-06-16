#include "Graphics.h"

Graphics* Graphics::hInstance = NULL;

Graphics::Graphics() 
{
	init();
}
Graphics::~Graphics() {}

Graphics* Graphics::instance()
{
	if (hInstance == NULL)
	{
		hInstance = new Graphics;
	}
	return hInstance;
}

void Graphics::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
	}
	hWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, hWindowWidth, hWindowHeight, SDL_WINDOW_SHOWN);
	if (hWindow == NULL) { std::cout << "Unable to create window: " << SDL_GetError() << '\n'; }
	hRenderer = SDL_CreateRenderer(hWindow, -1, SDL_RENDERER_ACCELERATED);
	std::cout << "renderer created!\n";
	if (hRenderer == NULL) { std::cout << "Unable to create renderer: " << SDL_GetError() << '\n'; }
	SDL_SetRenderDrawColor(hRenderer, 0, 0, 0, 0);
}

void Graphics::clearBuffer()
{
	SDL_RenderClear(hRenderer);
}

void Graphics::render()
{
	SDL_RenderPresent(hRenderer);
}

