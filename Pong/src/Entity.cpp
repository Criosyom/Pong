#include "Entity.h"

Entity* Entity::hInstance = NULL;

Entity::Entity(int xPos, int yPos)
{
	//hPos = ;
	hDstRect.x = xPos;
	hDstRect.y = yPos;

	hDstRect.w = 50;
	hDstRect.h = 501;
	//SDL_QueryTexture();

}

Entity::Entity() {}

Entity::~Entity() {}

Entity* Entity::instantiate(int xPos, int yPos)
{
	if (hInstance == NULL) { hInstance = new Entity(xPos,yPos); }

	

	return hInstance;
}


//
//void Entity::setTexture(const char* fileName)
//{
//	hTexClass->loadTexture(fileName);
//
//}
//
//void Entity::renderTexture(Texture* tex, SDL_Rect &srcRect)
//{
//	SDL_RenderCopy(tex->getGraphics()->getRenderer(), tex->getTexture(), &srcRect, &hDstRect);
//			//		^ WHAT EVEN IS THIS????
//						
//}

