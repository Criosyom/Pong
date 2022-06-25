#include "Collision.h"

Collision* Collision::hInstance = NULL;

Collision::Collision()
{
	texture = Texture::instance();
	timer = new Timer;
	leftScore.str("");
	leftScore << leftPoints;
	Text["playerPoints"].loadText("assets/bit5x3.ttf", leftScore.str().c_str(), { 255, 255, 255 }, 100.0f);
	rightScore.str("");
	rightScore << rightPoints;
	Text["opponentPoints"].loadText("assets/bit5x3.ttf", rightScore.str().c_str(), { 255, 255, 255 }, 100.0f);
}

Collision::~Collision()
{
	delete hInstance;
	hInstance = NULL;
	delete texture;
	texture = NULL;
}

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
	return false;
}

void Collision::titleCollisionCheck()
{
	std::srand(std::time(NULL));
	int randomLeft = -60 + (rand() % 120);
	int randomRight = 120 + (rand() % 120);
	if (SDL_HasIntersectionF(texture->Textures["titleBall"]->getDestRect(), texture->Textures["borderLeft"]->getDestRect()) && !titleLeft)
	{
		texture->Textures["titleBall"]->rotate(randomLeft);
		titleLeft = true;
		titleRight = titleTop = titleBottom = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["titleBall"]->getDestRect(), texture->Textures["borderRight"]->getDestRect()) && !titleRight)
	{
		texture->Textures["titleBall"]->rotate(randomRight);
		titleRight = true;
		titleLeft = titleTop = titleBottom = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["titleBall"]->getDestRect(), texture->Textures["borderTop"]->getDestRect()) && !titleTop)
	{
		texture->Textures["titleBall"]->speed = texture->Textures["titleBall"]->speed * Vector2{ 1.0f, -1.0f };
		titleTop = true;
		titleRight = titleLeft = titleBottom = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["titleBall"]->getDestRect(), texture->Textures["borderBottom"]->getDestRect()) && !titleBottom)
	{
		texture->Textures["titleBall"]->speed = texture->Textures["titleBall"]->speed * Vector2{ 1.0f, -1.0f };
		titleBottom = true;
		titleRight = titleTop = titleLeft = false;
	}

	if (texture->Textures["titleBall"]->getPos().x > texture->Textures["borderRight"]->getPos().x 
		|| texture->Textures["titleBall"]->getPos().x < texture->Textures["borderLeft"]->getPos().x
		|| texture->Textures["titleBall"]->getPos().y < texture->Textures["borderTop"]->getPos().y
		|| texture->Textures["titleBall"]->getPos().y > texture->Textures["borderBottom"]->getPos().y)
	{
		texture->Textures["titleBall"]->setPos(Vector2(graphics->getWindowWidth() / 2, graphics->getWindowHeight() / 2));
		titleBottom = titleRight = titleTop = titleLeft = false;
	}
}

void Collision::ballCollisionCheck(bool isGamePaused)
{
	// Chief, I'm like 99% sure there's a better way to do collision rather than doing a ton of if statements. But whatevs...

	std::srand(std::time(NULL));
	int randomTop = 130 + (rand() % 20);
	int randomMiddle = 160 + (rand() % 40);
	int randomBottom = 210 + (rand() % 20);
	int randomSpawn = 75 + (rand() % 375);
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleTop"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomTop);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleMiddle"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomMiddle);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["playerPaddleBottom"]->getDestRect()) && !bouncedPlayer)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomBottom);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedPlayer = true;
		bouncedOpponent = bouncedBottom = bouncedTop = false;
	}

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleTop"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomBottom - 180);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleMiddle"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomMiddle - 180);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["opponentPaddleBottom"]->getDestRect()) && !bouncedOpponent)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.05f, 1.05f };
		texture->Textures["ball"]->rotate(randomTop - 180);
		Mix_PlayChannel(-1, paddleSound, 0);
		bouncedOpponent = true;
		bouncedPlayer = bouncedBottom = bouncedTop = false;
	}

	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect()) && !bouncedTop)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };
		Mix_PlayChannel(-1, borderSound, 0);
		bouncedTop = true;
		bouncedBottom = bouncedBottomCheck = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["topBoundaryCheck"]->getDestRect()) && !bouncedTopCheck) 
	{
		bouncedTop = false; bouncedTopCheck = true;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect()) && !bouncedBottom)
	{
		texture->Textures["ball"]->speed = texture->Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };
		Mix_PlayChannel(-1, borderSound, 0);
		bouncedBottom = true;
		bouncedTop = bouncedTopCheck = false;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["bottomBoundaryCheck"]->getDestRect()) && !bouncedBottomCheck)
	{
		bouncedBottom = false; bouncedBottomCheck = true;
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["leftBoundary"]->getDestRect()))
	{
		touchedLeft = true;
	}
	if (touchedLeft && !isGamePaused)
	{
		timer->updateInstance();
		if (timer->getInstanceTime() < 2) 
		{ 
			rightPoints++; 
			Mix_PlayChannel(-1, scoreSound, 0);
			scored = true;
			SDL_DestroyTexture(Text["opponentPoints"].textTexture);
			rightScore.str("");
			rightScore << rightPoints;
			Text["opponentPoints"].loadText("assets/bit5x3.ttf", rightScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		}
		if (timer->getInstanceTime() > 100)
		{
			texture->Textures["ball"]->setPos(Vector2(graphics->getWindowWidth() / 2 + 70, randomSpawn));
			touchedLeft = bouncedPlayer = bouncedOpponent = bouncedBottom = bouncedTop = false;
			texture->Textures["ball"]->speed = Vector2(1.0f, 1.0f); 
			timer->resetInstance(); scored = false;
		}
	}
	if (SDL_HasIntersectionF(texture->Textures["ball"]->getDestRect(), texture->Textures["rightBoundary"]->getDestRect()))
	{

		touchedRight = true;
	}
	if (touchedRight && !isGamePaused)
	{
		timer->updateInstance();
		if (timer->getInstanceTime() < 2) 
		{	
			leftPoints++; 
			Mix_PlayChannel(-1, scoreSound, 0); 
			scored = true;
			SDL_DestroyTexture(Text["playerPoints"].textTexture);
			leftScore.str("");
			leftScore << leftPoints;
			Text["playerPoints"].loadText("assets/bit5x3.ttf", leftScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		}
		if (timer->getInstanceTime() > 100)
		{
			texture->Textures["ball"]->setPos(Vector2(graphics->getWindowWidth() / 2 - 70, randomSpawn));
			touchedRight = bouncedPlayer = bouncedOpponent = bouncedBottom = bouncedTop = false;
			texture->Textures["ball"]->speed = Vector2(1.0f, 1.0f);
			timer->resetInstance();	scored = false;
		}
	}
}