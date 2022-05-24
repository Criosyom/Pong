#include "Texture.h"



Texture::Texture(Vector2 startingPos)
{
	hPos.x = startingPos.x;
	hPos.y = startingPos.y;

	hGraphics = hGraphics->instance();
}

Texture::~Texture()
{
	delete hGraphics;
	hGraphics = NULL;
}


SDL_Texture* Texture::loadTexture(const char* fileName)
{
	hSurface = IMG_Load(fileName);
	if (hSurface == NULL) { std::cout << "Cannot load surface\n"; }
	hTexture = SDL_CreateTextureFromSurface(hGraphics->getRenderer(), hSurface);
	if (hTexture == NULL) { std::cout << "Cannot load texture: " << SDL_GetError() << '\n'; }

	SDL_FreeSurface(hSurface);

	return hTexture;

}

void Texture::renderTexture(int dstW, int dstH)
{
	hDestRect.x = hPos.x;
	hDestRect.y = hPos.y;
	hDestRect.w = dstW;
	hDestRect.h = dstH;
	SDL_RenderCopy(hGraphics->getRenderer(), hTexture, NULL, &hDestRect);
						
}

void Texture::renderClippedTexture(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH)
{
	hSrcRect.x = srcX;
	hSrcRect.y = srcY;
	hSrcRect.w = srcW;
	hSrcRect.h = srcH;
	hDestRect.x = hPos.x;
	hDestRect.y = hPos.y;
	hDestRect.w = dstW;
	hDestRect.h = dstH;
	SDL_RenderCopy(hGraphics->getRenderer(), hTexture, &hSrcRect, &hDestRect);

}