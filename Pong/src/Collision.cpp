#include "Collision.h"

Collision* Collision::hInstance = NULL;

Collision::Collision()
{
	texture = Texture::instance();
	timer = new Timer;
}

Collision::~Collision()
{}

Collision* Collision::instance()
{
	if (hInstance == NULL) { hInstance = new Collision; }
	return hInstance;
}

double distanceSquared(float x1, float y1, float x2, float y2)
{
	float deltaX = x2 - x1;
	float deltaY = y2 - y1;
	return pow(deltaX, 2) + pow(deltaY, 2);
}

bool circleBoxCollision(Texture* circle, Texture* box)
{
	// This took over a week to figure out... BUT NOW IT WORKS WOOOOOOOOOOOOOOOO!!!!
	int cX, cY;

	if (circle->getPos().x < box->getPos().x - box->getDestRect()->w / 2)
	{
		cX = box->getPos().x - box->getDestRect()->w / 2;
	}
	else if (circle->getPos().x > box->getPos().x + (box->getDestRect()->w / 2))
	{
		cX = box->getPos().x + box->getDestRect()->w / 2;
	}
	else
	{
		cX = circle->getPos().x;
	}
	if (circle->getPos().y < box->getPos().y - box->getDestRect()->h / 2)
	{
		cY = box->getPos().y - (box->getDestRect()->h / 2);
	}
	else if (circle->getPos().y > box->getPos().y + box->getDestRect()->h / 2)
	{
		cY = box->getPos().y + (box->getDestRect()->h / 2);
	}
	else
	{
		cY = circle->getPos().y;
	}

	float dS = distanceSquared(circle->getPos().x, circle->getPos().y, cX, cY);
	if (dS < pow(circle->getCircleCollider().r, 2) / 4)
	{
		return true;
	}

	std::cout << "Circle: { " << circle->getPos().x << ", " << circle->getPos().y << ", " << circle->getCircleCollider().r << " }	Closest point position: { " << cX << ", " << cY << " } " << "	Rec pos: { " << box->getPos().x << ", " << box->getPos().y << " }\n";
	return false;
}

void Collision::ballCollisionCheck()
{
	// Chief, I'm like 99% sure there's a better way to do collision rather than doing a ton of if statements. But whatevs...

	std::srand(std::time(0));
	int randomTop = 130 + (rand() % 20);
	int randomMiddle = 150 + (rand() % 60);
	int randomBottom = 210 + (rand() % 30);

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleTop"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomTop);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleMiddle"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomMiddle);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleBottom"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomBottom);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleTop"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomTop - 180);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleMiddle"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomMiddle - 180);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleBottom"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomBottom - 180);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect()) && !bouncedBottom)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };
		bouncedBottom = true;
		bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect()) && !bouncedTop)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };
		bouncedTop = true;
		bouncedBottom = false;
	}

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["leftBoundary"]->getDestRect()))
	{
		touchedLeft = true;
	}
	if (touchedLeft)
	{
		timer->updateInstance();
		if (timer->getInstanceTime() < 2) { rightPoints++; }
		if (timer->getInstanceTime() > 100)
		{
			texture->Textures["ball"]->setPos(Vector2(graphics->getWindowWidth() / 2 + 58, 200));
			touchedLeft = bouncedPlayer = bouncedOpponent = bouncedBottom = bouncedTop = false;
			texture->Textures["ball"]->speed = Vector2(1.0f, 1.0f);
			timer->resetInstance();
		}
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["rightBoundary"]->getDestRect()))
	{
		touchedRight = true;
	}
	if (touchedRight)
	{
		timer->updateInstance();
		if (timer->getInstanceTime() < 2) { leftPoints++; }
		if (timer->getInstanceTime() > 100)
		{
			texture->Textures["ball"]->setPos(Vector2(graphics->getWindowWidth() / 2 - 58, 200));
			touchedRight = bouncedPlayer = bouncedOpponent = bouncedBottom = bouncedTop = false;
			texture->Textures["ball"]->speed = Vector2(1.0f, 1.0f);
			timer->resetInstance();
		}
	}

	if (circleBoxCollision(texture->Textures["ball"], texture->Textures["playerPaddleMiddle"]))
	{
		std::cout << ".";
	}

}