#include "Game.h"

Game* Game::game = NULL;


Game::Game()
{
	hQuit = false;
	hGraphics = hGraphics->instance();

}

Game::~Game()
{
	delete game;
	game = NULL;
}


Game* Game::instance()
{
	if (game == NULL)
	{
		game = new Game;

	}
	return game;
}

void Game::loadContent()
{
	hGraphics->init();
	playerPaddle = new Texture;
	opponentPaddle = new Texture;
	middleLine = new Texture;
	ball = new Texture;

	playerPaddle->loadTexture("assets/pads.png");
	opponentPaddle->loadTexture("assets/pads.png");
	middleLine->loadTexture("assets/pads.png");
	ball->loadTexture("assets/ball.png");

}

void Game::run()
{
	while (!hQuit)
	{
		SDL_PollEvent(&hEvents);
		if (hEvents.type == SDL_QUIT) { hQuit = true; }



		hGraphics->clearBuffer();

		playerPaddle->renderTexture(30, hGraphics->getWindowHeight() / 2 - 25, 10, 50);
		opponentPaddle->renderTexture(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2 - 25, 10, 50);
		ball->renderTexture(hGraphics->getWindowWidth() / 2 - 11, hGraphics->getWindowHeight() / 2 - 10, 22, 20);
		for (int i = 0; i < 30; i++)
		{
			middleLine->renderTexture((hGraphics->getWindowWidth() / 2) - 1, i * 20, 2, 10);
		}

		hGraphics->render();
	}
}



