#pragma once
#include "Transform.h"
#include "SDL.h"
#include <iostream>
#define PI 3.14159265359
#define DEG_TO_RAD PI/180.0f



class Entity
{
public:

	void translate(Vector2 move);
	Vector2 speed = {1.0f , 1.0f};
	void rotate(double rotateDegrees);
	Vector2 getPos() { return hPos; }
	void setPos(Vector2 vec) { hPos = vec; }
	Vector2 getEntityOrigin() { return entityOrigin; }

	Entity(Vector2 vec);
	Entity();

	~Entity();
	double angle = 0;
protected:
	Vector2 hPos;
	float sizeX = 0.0f, sizeY = 0.0f;
	Vector2 entityOrigin;
};