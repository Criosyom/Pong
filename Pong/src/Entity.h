#pragma once
#include "Transform.h"
#include "SDL.h"
#include <iostream>
//#include "Texture.h"

class Entity
{
public:

	void translate(Vector2 move);

	Entity();
	~Entity();
protected:
	Vector2 hPos;


	
};