#include "Texture.h"

Texture* Texture::hInstance = NULL;

Texture::Texture(Vector2 startingPos_, Texture* setParent, const char* identicalTexture)
	: startingPos(startingPos_)
{
	hParent = setParent;
	hPos.x = setParent == NULL ? startingPos.x : hParent->hPos.x;
	hPos.y = setParent == NULL ? startingPos.y : hParent->hPos.y;
	sameTextureStr = identicalTexture;

	hGraphics = hGraphics->instance();
}

Texture::~Texture()
{
	delete hGraphics;
	hGraphics = NULL;
}

Texture* Texture::instance()
{
	if (hInstance == NULL)
	{
		hInstance = new Texture;
	}
	return hInstance;
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
	hDestRect.x = hParent == NULL ? hPos.x : hParent->hPos.x + startingPos.x;
	hDestRect.y = hParent == NULL ? hPos.y : hParent->hPos.y + startingPos.y;
	hDestRect.w = dstW;
	hDestRect.h = dstH;
	SDL_RenderCopyExF(hGraphics->getRenderer(), hTexture, NULL, &hDestRect, angle, NULL, SDL_FLIP_NONE);
						
}
//
//void Texture::renderClippedTexture(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH)
//{
//	hSrcRect.x = srcX;
//	hSrcRect.y = srcY;
//	hSrcRect.w = srcW;
//	hSrcRect.h = srcH;
//	hDestRect.x = hPos.x;
//	hDestRect.y = hPos.y;
//	hDestRect.w = dstW;
//	hDestRect.h = dstH;
//	SDL_RenderCopyF(hGraphics->getRenderer(), hTexture, &hSrcRect, &hDestRect);
//
//}