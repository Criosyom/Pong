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
	delete hInstance;
	hInstance = NULL;
	SDL_DestroyTexture(hTexture);
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
	file = fileName;
	hSurface = IMG_Load(fileName);
	if (hSurface == NULL) { std::cout << "Cannot load surface\n"; }
	hTexture = SDL_CreateTextureFromSurface(hGraphics->getRenderer(), hSurface);
	if (hTexture == NULL) { std::cout << "Cannot load texture: " << SDL_GetError() << '\n'; }
	SDL_FreeSurface(hSurface);

	return hTexture;
}

void Texture::renderTexture(float dstW, float dstH, float angleX, float angleY)
{
	sizeX = dstW;
	sizeY = dstH;
	hDestRect.x = hParent == NULL ? hPos.x - dstW / 2 : hParent->hPos.x + (startingPos.x - dstW / 2);
	hDestRect.y = hParent == NULL ? hPos.y - dstH / 2 : hParent->hPos.y + (startingPos.y - dstH / 2);
	hDestRect.w = sizeX;
	hDestRect.h = sizeY;
	entityOrigin = hPos;
	if (angleX == NULL && angleY == NULL) { anglePoint = { hDestRect.w / 2, hDestRect.h / 2 }; }
	else { anglePoint = { angleX, angleY }; }
	SDL_RenderCopyExF(hGraphics->getRenderer(), hTexture, NULL, &hDestRect, angle, &anglePoint, SDL_FLIP_NONE);
}

void Texture::addSize(float addSizeX, float addSizeY)
{
	sizeX += addSizeX;
	sizeY += addSizeY;
}
