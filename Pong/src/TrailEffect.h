#pragma once
#include "Texture.h"
#include <math.h>
struct TrailEffect
{
	TrailEffect();
	~TrailEffect();
	void loadTrail(Texture* ent, int capacity);
	void renderTrail(int maxAlpha, float sizeX = NULL, float sizeY = NULL);

	Texture* texture;
	Texture* entity;
	Graphics* hGraphics;
	int particleCap, particleCount, alphaDecreaseAmount, posLoop, alphaLoop, channel;
};