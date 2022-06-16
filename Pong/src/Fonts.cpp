#include "Fonts.h"

Fonts::Fonts()
{
	graphics = Graphics::instance();
}

Fonts::~Fonts()
{
	graphics = NULL;
	TTF_CloseFont(text);
}

void Fonts::loadText(const char* font, const char* displayText, SDL_Color textColor, float textSize)
{	
	if (TTF_Init() == -1) { std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n'; }
	text = TTF_OpenFont(font, textSize);
	if (text == NULL) { std::cout << "Cannot make text init: " << TTF_GetError() << '\n'; }
	surface = TTF_RenderText_Solid(text, displayText, textColor);
	if (surface == NULL) { std::cout << "Cannot make text surface: " << SDL_GetError() << '\n'; }
	textTexture = SDL_CreateTextureFromSurface(graphics->getRenderer(), surface);
	if (textTexture == NULL) { std::cout << "Cannot make text texture: " << TTF_GetError() << '\n'; }

	hWidth = surface->w;
	hHeight = surface->h;
	SDL_FreeSurface(surface);

}

void Fonts::renderText(int xPos, int yPos)
{
	dst.x = xPos - hWidth / 2;
	dst.y = yPos - hHeight / 2;
	dst.w = hWidth;
	dst.h = hHeight;
	SDL_RenderCopy(graphics->getRenderer(), textTexture, NULL, &dst);
}