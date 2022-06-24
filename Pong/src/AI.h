#pragma once
#include "SDL.h"
#include "Texture.h"
#include "Collision.h"
class AI
{
public:
	void aiBehavior(bool isSingle, bool isGamePaused);
	static AI* instance();
	AI();
	~AI();
private:
	Texture* texture;
	Collision* collision;
	static AI* hInstance;
};