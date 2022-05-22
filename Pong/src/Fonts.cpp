#include "Fonts.h"

Fonts::Fonts()
{
	graphics = Graphics::instance();

}

Fonts::~Fonts()
{

	graphics = NULL;
}

void Fonts::loadText(const char* font, const char* displayText, SDL_Color textColor, float textSize)
{	

	text = TTF_OpenFont(font, textSize);
	if (text == NULL) { std::cout << "Cannot make text init \n"; }
	surface = TTF_RenderText_Solid(text, displayText, textColor);
	if (surface == NULL) { std::cout << "Cannot make text surface \n"; }
	textTexture = SDL_CreateTextureFromSurface(graphics->getRenderer(), surface);
	if (textTexture == NULL) { std::cout << "Cannot make text texture \n"; }

	hWidth = surface->w;
	hHeight = surface->h;
	SDL_FreeSurface(surface);

}

void Fonts::renderText(int xPos, int yPos)
{
	dst.x = xPos;
	dst.y = yPos;
	dst.w = hWidth;
	dst.h = hHeight;
	SDL_RenderCopy(graphics->getRenderer(), textTexture, NULL, &dst);

}