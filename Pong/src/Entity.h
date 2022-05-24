#pragma once
#include "Transform.h"
#include "SDL.h"
#include <iostream>
//#include "Texture.h"

class Entity
{
public:

	void translate(Vector2 move);
	Vector2 speed = { 1.0f, 1.0f };
	Entity(Vector2 vec);
	Entity();

	~Entity();
protected:
	Vector2 hPos;
};