#pragma once
#include "Transform.h"
#include "SDL.h"
#include <iostream>
//#include "Texture.h"

class Entity
{
public:
	static Entity* instantiate(int xPos, int yPos);


	//void setTexture(const char* fileName);
	virtual void renderTexture(int dstX, int dstY, int dstW, int dstH) {};
	//virtual void renderTexture();
	virtual SDL_Texture* loadTexture(const char* fileName) { return NULL; };

	Entity(int xPos, int yPos);
	Entity();
	~Entity();
protected:
	Vector2 hPos;
	//Texture* hTexClass;
	SDL_Rect hSrcRect, hDstRect;

	static Entity* hInstance;

	
};