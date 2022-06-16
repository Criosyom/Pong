#pragma once
#include "SDL_image.h"
#include "Graphics.h"
#include "Entity.h"
#include <iostream>
#include <math.h>
#include <map>
#include <vector>

#define PI 3.14159265359
#define DEG_TO_RAD PI/180.0f

struct Circle
{
	float x = 300, y = 260, r = 11;
};

class Texture : public Entity
{
public:
	static Texture* instance();

	SDL_Texture* loadTexture(const char* fileName);
	void renderTexture(float dstW, float dstH, float angleX = NULL, float angleY = NULL);
	void renderClippedTexture(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);
	
	void addSize(float addSizeX = 0.0f, float addSizeY = 0.0f);

	Graphics* getGraphics() { return hGraphics; }
	SDL_Texture* getTexture() { return hTexture; }
	SDL_FRect* getDestRect() { return &hDestRect; }	
	Circle& getCircleCollider() { return hCircle; }

	std::map<std::string, Texture*> Textures = std::map<std::string, Texture*>();

	Texture(Vector2 startingPos = Vector2(0.0f, 0.0f), Texture* setParent = NULL, const char* identicalTexture = NULL);
	~Texture();

	const char* sameTextureStr = NULL;

	

private:

	SDL_Surface* hSurface;
	SDL_Texture* hTexture;
	Graphics* hGraphics;
	Vector2 startingPos;
	SDL_FRect hSrcRect, hDestRect;
	Circle hCircle;

	SDL_FPoint anglePoint;
	Texture* hParent;
	
	static Texture* hInstance;
};
