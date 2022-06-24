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
	float x, y, r;
};

class Texture : public Entity
{
public:
	static Texture* instance();

	SDL_Texture* loadTexture(const char* fileName);
	const char* file;
	void renderTexture(float dstW, float dstH, float angleX = NULL, float angleY = NULL);
	
	void addSize(float addSizeX = 0.0f, float addSizeY = 0.0f);

	Graphics* getGraphics() { return hGraphics; }
	SDL_Texture* getTexture() { return hTexture; }
	SDL_FRect* getDestRect() { return &hDestRect; }	
	Circle& getCircleCollider() { return hCircle; }

	std::map<std::string, Texture*> Textures = std::map<std::string, Texture*>();
	std::vector<std::vector<Texture*>> TexturesVectors;

	Texture(Vector2 startingPos = Vector2(0.0f, 0.0f), Texture* setParent = NULL, const char* identicalTexture = NULL);
	~Texture();

	const char* sameTextureStr = NULL;

private:
	SDL_Surface* hSurface;
	SDL_Texture* hTexture;
	Graphics* hGraphics;
	Vector2 startingPos;
	SDL_FRect hSrcRect, hDestRect;
	Circle hCircle = {hGraphics->getWindowWidth() / 2.0f, hGraphics->getWindowHeight() / 2.0f, 11.0f };

	SDL_FPoint anglePoint;
	Texture* hParent;
	
	static Texture* hInstance;
};
