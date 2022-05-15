#include "Texture.h"



Texture::Texture()
{

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

void Texture::renderTexture(int dstX, int dstY, int dstW, int dstH)
{
	hDestRect.x = dstX;
	hDestRect.y = dstY;
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
	hDestRect.x = dstX;
	hDestRect.y = dstY;
	hDestRect.w = dstW;
	hDestRect.h = dstH;
	SDL_RenderCopy(hGraphics->getRenderer(), hTexture, &hSrcRect, &hDestRect);

}