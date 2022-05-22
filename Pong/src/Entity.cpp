#include "Entity.h"


Entity::Entity() {}

Entity::~Entity() {}


void Entity::translate(Vector2 move)
{
	hPos += move;
}