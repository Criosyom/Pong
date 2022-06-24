#include "Entity.h"

Entity::Entity(Vector2 vec) 
{
	hPos += vec;
}

Entity::Entity() {}

Entity::~Entity() {}

void Entity::translate(Vector2 move)
{
	moving = true;
	hPos += Vector2((float)(cos(angle * DEG_TO_RAD) * move.x), (float)(sin(angle * DEG_TO_RAD) * move.x)) * speed;
	hPos += Vector2((float)(cos((angle + 90) * DEG_TO_RAD) * move.y), (float)(sin((angle + 90) * DEG_TO_RAD) * move.y)) * speed;
	//		^ These two took WAAAY too long to figure out
	//		It basically shifts the position of the entity based on its angle.
	//		Take the paddle, for example. When W is pressed, it moves up.							^
	//		However, if I rotate that paddle 90 degrees clockwise, then it will move to the right.  ^ (moves up) to > > (moves right)
}

void Entity::rotate(double rotateDegrees)
{
	angle = rotateDegrees;
}
