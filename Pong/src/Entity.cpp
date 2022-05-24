#include "Entity.h"


Entity::Entity(Vector2 vec) 
{
	hPos += vec;
}

Entity::Entity() {}

Entity::~Entity() {}


void Entity::translate(Vector2 move)
{
	hPos += move * speed;
}