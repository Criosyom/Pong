#include "Fonts.h"

Fonts::Fonts()
{
	graphics = Graphics::instance();
}

Fonts::~Fonts()
{
	delete graphics;
	graphics = NULL;
	TTF_CloseFont(text);
}

void Fonts::loadText(const char* font, const char* displayText, SDL_Color textColor, float textSize, Uint32 wrapSize)
{	
	if (TTF_Init() == -1) { std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n'; }
	text = TTF_OpenFont(font, textSize);
	if (text == NULL) { std::cout << "Cannot make text init: " << TTF_GetError() << '\n'; }
	surface = TTF_RenderText_Solid_Wrapped(text, displayText, textColor, wrapSize = NULL);
	if (surface == NULL) { std::cout << "Cannot make text surface: " << SDL_GetError() << '\n'; }
	textTexture = SDL_CreateTextureFromSurface(graphics->getRenderer(), surface);
	if (textTexture == NULL) { std::cout << "Cannot make text texture: " << TTF_GetError() << '\n'; }
	hWidth = surface->w;
	hHeight = surface->h;
	SDL_FreeSurface(surface);
}

void Fonts::renderText(int xPos, int yPos, bool fromTopLeft)
{
	dst.x = fromTopLeft ? xPos : xPos - hWidth / 2;
	dst.y = fromTopLeft ? yPos : yPos - hHeight / 2;
	dst.w = hWidth;
	dst.h = hHeight;
	SDL_RenderCopy(graphics->getRenderer(), textTexture, NULL, &dst);
}