#include "AI.h"

AI* AI::hInstance = NULL;

AI::AI()
{
	texture = Texture::instance();
	collision = Collision::instance();
}

AI::~AI()
{
	delete texture;
	texture = NULL;
	delete collision;
	collision = NULL;
}

AI* AI::instance()
{
	if (hInstance == NULL) { hInstance = new AI; }
	return hInstance;
}

void AI::aiBehavior(bool isSingle, bool isGamePaused)
{
	texture->Textures["opponentPaddleMiddle"]->moving = false;
	if (isSingle && !isGamePaused)
	{
		if (texture->Textures["opponentPaddleMiddle"]->getPos().y > texture->Textures["ball"]->getPos().y
			&& !SDL_HasIntersectionF(texture->Textures["opponentPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect())
			&& !collision->scored
			&& texture->Textures["ball"]->angle > 90)
		{
			texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, -4.2f));
		}
		if (texture->Textures["opponentPaddleMiddle"]->getPos().y < texture->Textures["ball"]->getPos().y
			&& !SDL_HasIntersectionF(texture->Textures["opponentPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect())
			&& !collision->scored
			&& texture->Textures["ball"]->angle > 90)
		{
			texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, 4.2f));
		}
	}
}