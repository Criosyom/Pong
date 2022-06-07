#include "Game.h"

Game* Game::game = NULL;


Game::Game()
{
	hQuit = false;
	hGraphics = hGraphics->instance();
	hCollision = Collision::instance();
	texture = Texture::instance();
	SDL_Init(SDL_INIT_EVERYTHING);
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
	texture->Textures["playerPaddleMiddle"] = new Texture(Vector2(40, hGraphics->getWindowHeight() / 2));
	texture->Textures["playerPaddleTop"] = new Texture(Vector2(0, -20), texture->Textures["playerPaddleMiddle"], "pads");
	texture->Textures["playerPaddleBottom"] = new Texture(Vector2(0, 20), texture->Textures["playerPaddleMiddle"], "pads");
	texture->Textures["opponentPaddleMiddle"] = new Texture(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2), NULL, "pads");
	texture->Textures["opponentPaddleTop"] = new Texture(Vector2(0, -20), texture->Textures["opponentPaddleMiddle"], "pads");
	texture->Textures["opponentPaddleBottom"] = new Texture(Vector2(0, 20), texture->Textures["opponentPaddleMiddle"], "pads");
	texture->Textures["middleLine"] = new Texture(NULL, NULL, "pads");
	texture->Textures["ball"] = new Texture(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
	texture->Textures["test"] = new Texture();
	texture->Textures["topBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, -3.0f), NULL, "pads");
	texture->Textures["bottomBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() + 3.0f), NULL, "pads");
	texture->Textures["leftBoundary"] = new Texture(Vector2(-3.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");
	texture->Textures["rightBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() + 3.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");

	texture->Textures["playerPaddleMiddle"]->loadTexture("assets/red.png");
	texture->Textures["ball"]->loadTexture("assets/ballWhite.png");
	//texture->Textures["test"]->loadTexture("assets/ball.png");

	for (std::pair<std::string, Texture*> t : texture->Textures)
	{
		if (t.second->sameTextureStr == "pads")
		{
			t.second->loadTexture("assets/pads.png");
		}
	}
	Text["fpsText"].loadText("assets/Hakugyokurou.ttf", "fps", { 255, 255, 255 }, 14.0f);
}

void Game::run()
{
	Timer timer;
	while (!hQuit)
	{
		//SDL_FRect rectToDraw = { texture->Textures["ball"]->getPos().x, texture->Textures["ball"]->getPos().y,100,100 };
		timer.startTime();
		SDL_PollEvent(&hEvents);

		if (hEvents.type == SDL_QUIT) { hQuit = true; }
		float avgFps = countedFrames / (timer.getStartTime() / 1000.0f);
		fpsCount.str("");
		fpsCount << roundf(avgFps * 10) / 10;
		leftScore.str("");
		leftScore << hCollision->leftPoints;
		rightScore.str("");
		rightScore << hCollision->rightPoints;
		Text["avgFpsText"].loadText("assets/Hakugyokurou.ttf", fpsCount.str().c_str(), {255, 255, 255}, 14.0f);
		Text["playerPoints"].loadText("assets/bit5x3.ttf", leftScore.str().c_str(), {255, 255, 255}, 80.0f);
		Text["opponentPoints"].loadText("assets/bit5x3.ttf", rightScore.str().c_str(), {255, 255, 255}, 80.0f);

		bool collidedTop = SDL_HasIntersectionF(texture->Textures["playerPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect());
		bool collidedBottom = SDL_HasIntersectionF(texture->Textures["playerPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect());
		if (inputs.currentKeyStates[SDL_SCANCODE_W] && !inputs.currentKeyStates[SDL_SCANCODE_S] && !collidedTop)
		{
			texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, -6.0f));
			texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, -6.0f));
		}
		if (inputs.currentKeyStates[SDL_SCANCODE_S] && !collidedBottom)
		{
			texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, 6.0f));
			texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, 6.0f));
		}
		if (inputs.currentKeyStates[SDL_SCANCODE_A] && !inputs.currentKeyStates[SDL_SCANCODE_D])
		{
			texture->Textures["playerPaddleMiddle"]->translate(Vector2(-6.0f, 0.0f));
		}
		if (inputs.currentKeyStates[SDL_SCANCODE_D])
		{
			texture->Textures["playerPaddleMiddle"]->translate(Vector2(6.0f, 0.0f));
		}

		texture->Textures["ball"]->translate(Vector2(-7.0f, 0.0f));
		hCollision->ballCollisionCheck();
		//texture->Textures["ball"]->addSize(5, 0);
		SDL_SetRenderDrawColor(hGraphics->getRenderer(), 0, 0, 0, 0);
		hGraphics->clearBuffer();
		SDL_SetRenderDrawColor(hGraphics->getRenderer(), 255, 255, 255, 0);
		texture->Textures["playerPaddleTop"]->renderTexture(10, 20);
		texture->Textures["playerPaddleMiddle"]->renderTexture(10, 20);
		texture->Textures["playerPaddleBottom"]->renderTexture(10, 20);
		texture->Textures["opponentPaddleTop"]->renderTexture(10, 20);
		texture->Textures["opponentPaddleMiddle"]->renderTexture(10, 20);
		texture->Textures["opponentPaddleBottom"]->renderTexture(10, 20);
		texture->Textures["ball"]->renderTexture(texture->getCircleCollider().r, texture->getCircleCollider().r);
		texture->Textures["test"]->setPos(texture->Textures["ball"]->getEntityOrigin());
		texture->Textures["test"]->renderTexture(100, 100);
		/*if (SDL_HasIntersectionF(texture->Textures["playerPaddleBottom"]->getDestRect(), texture->Textures["ball"]->getDestRect()))
		{
			std::cout << ".";
		}*/
		for (int i = 0; i < 27; i++)
		{
			mid.x = (hGraphics->getWindowWidth() / 2) - 1;
			mid.y = i * 20;
			mid.w = 2;
			mid.h = 10;
			SDL_RenderCopyF(hGraphics->getRenderer(), texture->Textures["middleLine"]->getTexture(), NULL, &mid);
		}
		texture->Textures["topBoundary"]->renderTexture(hGraphics->getWindowWidth(), 6);
		texture->Textures["bottomBoundary"]->renderTexture(hGraphics->getWindowWidth(), 6);
		texture->Textures["leftBoundary"]->renderTexture(6, hGraphics->getWindowHeight());
		texture->Textures["rightBoundary"]->renderTexture(6, hGraphics->getWindowHeight());

		Text["avgFpsText"].renderText(hGraphics->getWindowWidth() - 50, hGraphics->getWindowHeight() - 15);
		Text["fpsText"].renderText(hGraphics->getWindowWidth() - 22, hGraphics->getWindowHeight() - 15);
		Text["playerPoints"].renderText(hGraphics->getWindowWidth() / 2 - 80, 30);
		Text["opponentPoints"].renderText(hGraphics->getWindowWidth() / 2 + 55, 30);

		//SDL_RenderDrawRectF(hGraphics->getRenderer(), &rectToDraw);

		hGraphics->render();

		float frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS))
		{
			SDL_Delay((1000.0f/FPS) - frameTicks);
		}
	}
}
