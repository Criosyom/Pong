#include "TrailEffect.h"

TrailEffect::TrailEffect()	
{
	hGraphics = Graphics::instance();
	texture = Texture::instance();
}

TrailEffect::~TrailEffect()	{}

void TrailEffect::loadTrail(Texture* ent, int capacity)
{
	entity = ent;
	particleCap = capacity;
	texture->TexturesVectors.emplace_back();
	std::cout << texture->TexturesVectors.size() << '\n';
	channel = texture->TexturesVectors.size() - 1;
	for (int particleLoad = 0; particleLoad < particleCap; particleLoad++)
	{
		texture->TexturesVectors[channel].emplace_back();
		texture->TexturesVectors[channel][particleCount] = new Texture(Vector2(entity->getPos().x, entity->getPos().y));
		texture->TexturesVectors[channel][particleCount]->loadTexture(ent->file);
		if (texture->TexturesVectors[channel].size() < particleCap) { particleCount++; }
	}
}

void TrailEffect::renderTrail(int maxAlpha, float sizeX, float sizeY)
{
	if (entity->moving)
	{
		sizeX == NULL ? sizeX = entity->getDestRect()->w : sizeX;
		sizeY == NULL ? sizeY = entity->getDestRect()->h : sizeY;
		if (texture->TexturesVectors[channel].size() == particleCap)
		{
			for (alphaLoop = 0; alphaLoop < particleCap; alphaLoop++)
			{
				alphaDecreaseAmount = maxAlpha - (posLoop - alphaLoop) * maxAlpha / particleCap;
				if (alphaDecreaseAmount > maxAlpha) { alphaDecreaseAmount %= maxAlpha; }
				if (alphaDecreaseAmount < 0) { alphaDecreaseAmount %= -maxAlpha + maxAlpha; }
				SDL_SetTextureBlendMode(texture->TexturesVectors[channel][alphaLoop]->getTexture(), SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(texture->TexturesVectors[channel][alphaLoop]->getTexture(), alphaDecreaseAmount);
			}
			texture->TexturesVectors[channel][posLoop]->setPos(Vector2(entity->getPos().x, entity->getPos().y));
			posLoop++;
			if (posLoop >= particleCap) { posLoop = 0; }
		}
		for (int i = 0; i <= particleCount; i++)
		{
			texture->TexturesVectors[channel][particleCount - i]->renderTexture(sizeX, sizeY);
		}
	}
	// I absolutely do NOT know how this works even though I wrote it myself.
	// But it works, so I'm not going to think too hard. 
}