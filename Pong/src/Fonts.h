#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Graphics.h"
#include <string>
#include <iostream>

class Fonts
{
private:
	TTF_Font* text;
	SDL_Surface* surface;
	SDL_Texture* textTexture;
	Graphics* graphics;

public:
	Fonts();
	~Fonts();
	void loadText(const char* font, const char* displayText, SDL_Color textColor, float textSize);
	void renderText(int posX, int posY);
	int hWidth, hHeight;
	SDL_Rect dst;

};