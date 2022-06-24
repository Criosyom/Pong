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
	Graphics* graphics;

public:
	Fonts();
	~Fonts();
	void loadText(const char* font, const char* displayText, SDL_Color textColor, float textSize, Uint32 wrapSize = NULL);
	void renderText(int posX, int posY, bool fromTopLeft = false);
	int hWidth, hHeight;
	SDL_Rect dst;
	SDL_Texture* textTexture;
};