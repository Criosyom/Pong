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
	if (TTF_Init() == -1) { std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n'; }
	playerPaddle = new Texture;
	opponentPaddle = new Texture;
	middleLine = new Texture;
	ball = new Texture;

	playerPaddle->loadTexture("assets/pads.png");
	opponentPaddle->loadTexture("assets/pads.png");
	middleLine->loadTexture("assets/pads.png");
	ball->loadTexture("assets/ball.png");

	playerPaddle->translate(Vector2(30, hGraphics->getWindowHeight() / 2 - 25 ));
	opponentPaddle->translate(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2 - 25 ));
	middleLine->translate(Vector2((hGraphics->getWindowWidth() / 2) - 1, 20 ));
	ball->translate(Vector2(hGraphics->getWindowWidth() / 2 - 11, hGraphics->getWindowHeight() / 2 - 10 ));
	
	fonts2ElectricBoogaloo.loadText("assets/Hakugyokurou.ttf", "fps", { 255, 255, 255 }, 14.0f);

}

void Game::run()
{
	Timer timer;
	while (!hQuit)
	{
		timer.startTime();
		SDL_PollEvent(&hEvents);
		if (hEvents.type == SDL_QUIT) { hQuit = true; }
		float avgFps = countedFrames / (timer.getStartTime() / 1000.0f);
		stream.str("");
		stream << roundf(avgFps * 10) / 10;
		fonts.loadText("assets/Hakugyokurou.ttf", stream.str().c_str(), {255, 255, 255}, 14.0f);


		if (inputs.currentKeyStates[SDL_SCANCODE_W] && !inputs.currentKeyStates[SDL_SCANCODE_S])
		{
			playerPaddle->translate(Vector2(0.0f, -7.0f));
		}
		if (inputs.currentKeyStates[SDL_SCANCODE_S])
		{
			playerPaddle->translate(Vector2(0.0f, 7.0f));
		}


		hGraphics->clearBuffer();

		playerPaddle->renderTexture(10, 50);
		opponentPaddle->renderTexture(10, 50);
		ball->renderTexture(22, 20);
		for (int i = 0; i < 27; i++)
		{
			SDL_Rect mid;
			mid.x = (hGraphics->getWindowWidth() / 2) - 1;
			mid.y = i * 20;
			mid.w = 2;
			mid.h = 10;
			SDL_RenderCopy(hGraphics->getRenderer(), middleLine->getTexture(), NULL, &mid);
		}

		fonts.renderText(hGraphics->getWindowWidth() - 50, hGraphics->getWindowHeight() - 15);
		fonts2ElectricBoogaloo.renderText(hGraphics->getWindowWidth() - 22, hGraphics->getWindowHeight() - 15);
		hGraphics->render();

		float frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS))
		{
			SDL_Delay((1000.0f/FPS) - frameTicks);
		}
	}
}



