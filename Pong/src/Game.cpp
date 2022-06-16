#include "Game.h"

uint32_t TotalAllocated = 0;
uint32_t TotalFreed = 0;

void* operator new(size_t size)
{
	TotalAllocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	TotalFreed += size;
	free(memory);
}

Game* Game::game = NULL;

Game* Game::instance()
{
	if (game == NULL)
	{
		game = new Game;
	}
	return game;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	hGraphics = hGraphics->instance();
	hQuitTitle = hQuitGame = false;
	texture = Texture::instance();
	hAI = AI::instance();
	hCollision = hCollision->instance();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

Game::~Game()
{
	delete game;
	game = NULL;
	SDL_DestroyWindow(hGraphics->getWindow());
	SDL_DestroyRenderer(hGraphics->getRenderer());
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::titleScreen()
{
	hCollision->selectSound = Mix_LoadWAV("assets/select2.wav");
	hCollision->Text["PONG"].loadText("assets/Hakugyokurou.ttf", "PONG", { 255, 255, 255 }, 125.0f);
	while (!hQuitTitle)
	{
		timer.startTime();
		hGraphics->clearBuffer();
		SDL_PollEvent(&hEvents);
		if (hEvents.type == SDL_QUIT) { hQuitTitle = true; }
		hCollision->Text["Polyvinyl Chloride"].loadText("assets/Hakugyokurou.ttf", "Player VS Computer", inputs.PVCColor, 30.0f);
		hCollision->Text["PVP"].loadText("assets/Hakugyokurou.ttf", "Player VS Player", inputs.PVPColor, 30.0f);
		hCollision->Text["SPEED"].loadText("assets/Hakugyokurou.ttf", "SUPER SPEED", inputs.SPEEDColor, 30.0f);
		hCollision->Text["ExitGame"].loadText("assets/Hakugyokurou.ttf", "Exit game", inputs.ExitColor, 30.0f);
		switch (inputs.mouseEvents(&hEvents))
		{
		case 1: hQuitTitle = true; singlePlayer = true; break;
		case 2: hQuitTitle = true; singlePlayer = false; break;
		case 3: hQuitTitle = true; singlePlayer = true; FPS = 600.0f; break;
		case 4: hQuitTitle = true; hQuitGame = true; break;
		}		
		hCollision->Text["PONG"].renderText(hGraphics->getWindowWidth() / 2, 100);
		hCollision->Text["Polyvinyl Chloride"].renderText(hGraphics->getWindowWidth() / 2, 250);
		hCollision->Text["PVP"].renderText(hGraphics->getWindowWidth() / 2, 310);
		hCollision->Text["SPEED"].renderText(hGraphics->getWindowWidth() / 2, 370);
		hCollision->Text["ExitGame"].renderText(hGraphics->getWindowWidth() / 2, 430);

		hGraphics->render();		
		
		frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS))
		{
			SDL_Delay((1000.0f / FPS) - frameTicks);
		}
	}
}

void Game::loadContent()
{
	texture->Textures["playerPaddleMiddle"] = new Texture(Vector2(40, hGraphics->getWindowHeight() / 2));
	texture->Textures["playerPaddleTop"] = new Texture(Vector2(0, -17), texture->Textures["playerPaddleMiddle"], "pads");
	texture->Textures["playerPaddleBottom"] = new Texture(Vector2(0, 17), texture->Textures["playerPaddleMiddle"], "pads");
	texture->Textures["opponentPaddleMiddle"] = new Texture(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2), NULL, "pads");
	texture->Textures["opponentPaddleTop"] = new Texture(Vector2(0, -17), texture->Textures["opponentPaddleMiddle"], "pads");
	texture->Textures["opponentPaddleBottom"] = new Texture(Vector2(0, 17), texture->Textures["opponentPaddleMiddle"], "pads");
	texture->Textures["middleLine"] = new Texture(NULL, NULL, "pads");
	texture->Textures["ball"] = new Texture(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
	texture->Textures["topBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, -3.0f), NULL, "pads");
	texture->Textures["bottomBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() + 3.0f), NULL, "pads");
	texture->Textures["leftBoundary"] = new Texture(Vector2(-3.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");
	texture->Textures["rightBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() + 3.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");

	texture->Textures["playerPaddleMiddle"]->loadTexture("assets/red.png");
	texture->Textures["ball"]->loadTexture("assets/ballWhite.png");
	hCollision->paddleSound = Mix_LoadWAV("assets/pongCollidePaddle.wav");
	hCollision->borderSound = Mix_LoadWAV("assets/borderCollision.wav");
	hCollision->scoreSound = Mix_LoadWAV("assets/scored.wav");
	countDown = Mix_LoadWAV("assets/select.wav");
	for (std::pair<std::string, Texture*> t : texture->Textures)
	{
		if (t.second->sameTextureStr == "pads")
		{
			t.second->loadTexture("assets/pads.png");
		}
	}
	hCollision->Text["fpsText"].loadText("assets/Hakugyokurou.ttf", "fps", { 255, 255, 255 }, 14.0f);
}

void Game::run()
{
	while (!hQuitGame)
	{
		timer.startTime();
		timer.updateInstance();
		hGraphics->clearBuffer();

		while (SDL_PollEvent(&hEvents))
		{
			if (hEvents.type == SDL_QUIT) { hQuitGame = true; }
		}

		float avgFps = countedFrames / (timer.getStartTime() / 1000.0f);
		fpsCount.str("");
		fpsCount << roundf(avgFps * 10) / 10;
		hCollision->Text["avgFpsText"].loadText("assets/Hakugyokurou.ttf", fpsCount.str().c_str(), {255, 255, 255}, 14.0f);
		inputs.keyboardEvents(singlePlayer);
		

		hAI->aiBehavior(singlePlayer);
		hCollision->ballCollisionCheck();

		if (timer.getInstanceTime() <= 35)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "3", { 255, 255, 255 }, 50.0f);
			if (!soundPlayed3) { Mix_PlayChannel(-1, countDown, 0); soundPlayed3 = true; }
		}
		if (timer.getInstanceTime() <= 70 && timer.getInstanceTime() > 35)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "2", { 255, 255, 255 }, 50.0f);
			if (!soundPlayed2) { Mix_PlayChannel(-1, countDown, 0); soundPlayed2 = true; }
		}
		if (timer.getInstanceTime() <= 105 && timer.getInstanceTime() > 70)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "1", { 255, 255, 255 }, 50.0f);
			if (!soundPlayed1) { Mix_PlayChannel(-1, countDown, 0); soundPlayed1 = true; }
		}
		if (timer.getInstanceTime() > 105)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", " ", { 255, 255, 255 }, 50.0f);
			texture->Textures["ball"]->translate(Vector2(-7.0f, 0.0f));
		}

		texture->Textures["playerPaddleTop"]->renderTexture(9, 21);
		texture->Textures["playerPaddleMiddle"]->renderTexture(9, 13);
		texture->Textures["playerPaddleBottom"]->renderTexture(9, 21);
		texture->Textures["opponentPaddleTop"]->renderTexture(9, 21);
		texture->Textures["opponentPaddleMiddle"]->renderTexture(9, 13);
		texture->Textures["opponentPaddleBottom"]->renderTexture(9, 21);
		texture->Textures["ball"]->renderTexture(texture->getCircleCollider().r, texture->getCircleCollider().r);
	/*	texture->Textures["test"]->setPos(texture->Textures["ball"]->getEntityOrigin() - texture->Textures["test"]->getDestRect()->w / 2);
		texture->Textures["test"]->rotate(texture->Textures["ball"]->angle);
		texture->Textures["test"]->renderTexture(7 * texture->Textures["ball"]->speed.x + 70, 10, texture->Textures["test"]->getDestRect()->w, texture->Textures["test"]->getDestRect()->h / 2);*/
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

		hCollision->Text["avgFpsText"].renderText(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() - 10);
		hCollision->Text["fpsText"].renderText(hGraphics->getWindowWidth() - 12, hGraphics->getWindowHeight() - 10);
		hCollision->Text["playerPoints"].renderText(hGraphics->getWindowWidth() / 2 - 74, 70);
		hCollision->Text["opponentPoints"].renderText(hGraphics->getWindowWidth() / 2 + 86, 70);
		hCollision->Text["countDown"].renderText(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() / 2);

		hAI->aiBehavior(singlePlayer);

		hGraphics->render();

		//std::cout << "Total memory usage: " << TotalAllocated - TotalFreed << "\n";
		frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS))
		{
			SDL_Delay((1000.0f/FPS) - frameTicks);
		}
	}
}
