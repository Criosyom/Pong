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
	if (!titleInitialized) 
	{
		texture->Textures["titleBall"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() / 2));
		texture->Textures["borderTop"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, -10.0f));
		texture->Textures["borderBottom"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() + 10.0f));
		texture->Textures["borderLeft"] = new Texture(Vector2(-10.0f, hGraphics->getWindowHeight() / 2));
		texture->Textures["borderRight"] = new Texture(Vector2(hGraphics->getWindowWidth() + 10.0f, hGraphics->getWindowHeight() / 2));
		texture->Textures["titleBall"]->loadTexture("assets/ballWhite.png");
		titleBallTrail.loadTrail(texture->Textures["titleBall"], 6);
		hCollision->selectSound = Mix_LoadWAV("assets/select2.wav");
		hCollision->Text["PONG"].loadText("assets/BlippoBold.ttf", "PONG", {255, 255, 255}, 125.0f);
		hCollision->Text["spaceToStop"].loadText("assets/Hakugyokurou.ttf", " ", { 255, 255, 255 }, 15.0f);
		titleInitialized = true;
	}
	while (!hQuitTitle)
	{
		timer.startTime();
		hGraphics->clearBuffer();
		SDL_PollEvent(&hEvents);
		if (hEvents.type == SDL_QUIT) { hQuitTitle = true; hQuitGame = true; }

		if (!titleTextsLoaded || inputs.titleOptimizer < 2 && inputs.titleOptimizer2 < 2 
			|| inputs.titleOptimizer3 < 2 && inputs.titleOptimizer4 < 2 || inputs.titleOptimizer5 < 2 && inputs.titleOptimizer6 < 2)
		{
			hCollision->Text["Polyvinyl Chloride"].loadText("assets/Hakugyokurou.ttf", "Player VS Computer", inputs.PVCColor, 30.0f);
			hCollision->Text["PVP"].loadText("assets/Hakugyokurou.ttf", "Player VS Player", inputs.PVPColor, 30.0f);
			hCollision->Text["QuitGame"].loadText("assets/Hakugyokurou.ttf", "Quit game", inputs.QuitColor, 30.0f);
			titleTextsLoaded = true;
		}
		hCollision->titleCollisionCheck();
		texture->Textures["titleBall"]->translate(Vector2(inputs.titleBallSpeed, 0.0f));
		switch (inputs.mouseEvents(&hEvents))
		{
		case 1: hQuitTitle = true; hQuitGame = false; singlePlayer = true; 
		hCollision->Text["instructions"].loadText("assets/SunflowerHighway.otf", "Up = W or Up Arrow\n\nDown = S or Down Arrow", { 255, 255, 255 }, 25.0f); 
		break;
		case 2: hQuitTitle = true; hQuitGame = false; singlePlayer = false; 
		hCollision->Text["instructions"].loadText("assets/SunflowerHighway.otf", "Up = W\n\nDown = S", { 255, 255, 255 }, 25.0f); 
		break;
		case 3: hQuitTitle = true; hQuitGame = true; break;
		}		
		inputs.titleKeyBoardEvents(&hEvents);
		hCollision->Text["PONG"].renderText(hGraphics->getWindowWidth() / 2, 100);
		hCollision->Text["Polyvinyl Chloride"].renderText(hGraphics->getWindowWidth() / 2, 260);
		hCollision->Text["PVP"].renderText(hGraphics->getWindowWidth() / 2, 330);
		hCollision->Text["QuitGame"].renderText(hGraphics->getWindowWidth() / 2, 400);
		if (!inputs.musicStop)
		{
			hCollision->Text["spaceToStop"].renderText(hGraphics->getWindowWidth() - 120,hGraphics->getWindowHeight() - 12);
		}
		texture->Textures["titleBall"]->renderTexture(inputs.titleBallWidth, inputs.titleBallHeight);
		texture->Textures["borderTop"]->renderTexture(hGraphics->getWindowWidth(), 20);
		texture->Textures["borderBottom"]->renderTexture(hGraphics->getWindowWidth(), 20);
		texture->Textures["borderLeft"]->renderTexture(20, hGraphics->getWindowHeight());
		texture->Textures["borderRight"]->renderTexture(20, hGraphics->getWindowHeight());
		if (inputs.musicStop) { titleBallTrail.renderTrail(100); }
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
	if (!gameInitialized)
	{
		texture->Textures["playerPaddleMiddle"] = new Texture(Vector2(40, hGraphics->getWindowHeight() / 2), NULL, "pads");
		texture->Textures["playerPaddleTop"] = new Texture(Vector2(0, -17), texture->Textures["playerPaddleMiddle"], "pads");
		texture->Textures["playerPaddleBottom"] = new Texture(Vector2(0, 17), texture->Textures["playerPaddleMiddle"], "pads");
		texture->Textures["opponentPaddleMiddle"] = new Texture(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2), NULL, "pads");
		texture->Textures["opponentPaddleTop"] = new Texture(Vector2(0, -17), texture->Textures["opponentPaddleMiddle"], "pads");
		texture->Textures["opponentPaddleBottom"] = new Texture(Vector2(0, 17), texture->Textures["opponentPaddleMiddle"], "pads");
		texture->Textures["middleLine"] = new Texture(NULL, NULL, "pads");
		texture->Textures["ball"] = new Texture(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
		texture->Textures["topBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, -10.0f), NULL, "pads");
		texture->Textures["bottomBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() + 10.0f), NULL, "pads");
		texture->Textures["topBoundaryCheck"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, -14.0f), NULL, "pads");
		texture->Textures["bottomBoundaryCheck"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() + 14.0f), NULL, "pads");
		texture->Textures["leftBoundary"] = new Texture(Vector2(-10.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");
		texture->Textures["rightBoundary"] = new Texture(Vector2(hGraphics->getWindowWidth() + 10.0f, hGraphics->getWindowHeight() / 2), NULL, "pads");
		
		hCollision->Text["gameOver()"].loadText("assets/SunflowerHighway.otf", "(Btw if you press any letter key on the title screen, something stupid might happen)", { 255, 255, 255 }, 15.0f);
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
		ballTrail.loadTrail(texture->Textures["ball"], 6);
		leftPaddleTrail.loadTrail(texture->Textures["playerPaddleMiddle"], 11);
		rightPaddleTrail.loadTrail(texture->Textures["opponentPaddleMiddle"], 11);
		hCollision->Text["instructions2"].loadText("assets/SunflowerHighway.otf", "Up = Up Arrow\n\nDown = Down Arrow", { 255, 255, 255 }, 25.0f);
		hCollision->Text["fpsText"].loadText("assets/Hakugyokurou.ttf", "fps", { 255, 255, 255 }, 14.0f);
		std::srand(std::time(NULL)); oddOrEven = rand() % 2;
		oddOrEven < 1 ? texture->Textures["ball"]->rotate(180) : texture->Textures["ball"]->rotate(0);
		gameInitialized = true;
	}
}

void Game::run()
{
	while (!hQuitGame)
	{
		timer.startTime();
		float avgFps = countedFrames / (timer.getStartTime() / 1000.0f);
		fpsCount.str("");
		fpsCount << roundf(avgFps * 10) / 10;
		hCollision->Text["avgFpsText"].loadText("assets/Hakugyokurou.ttf", fpsCount.str().c_str(), { 255, 255, 255 }, 14.0f);
		
		if (!gamePaused) { timer.updateInstance(); }
		SDL_PollEvent(&hEvents);
		if (hEvents.type == SDL_QUIT) { hQuitTitle = true; hQuitGame = true; }
		if (!gameOver)
		{
			if (inputs.currentKeyStates[SDL_SCANCODE_ESCAPE] && !gamePaused && keyReleased2 || inputs.currentKeyStates[SDL_SCANCODE_P] && !gamePaused && keyReleased2) { gamePaused = true; keyReleased = false; }
			if (hEvents.type == SDL_KEYUP && gamePaused) { if (hEvents.key.keysym.sym == SDLK_ESCAPE || hEvents.key.keysym.sym == SDLK_p) { keyReleased = true; } }
			if (inputs.currentKeyStates[SDL_SCANCODE_ESCAPE] && gamePaused && keyReleased || inputs.currentKeyStates[SDL_SCANCODE_P] && gamePaused && keyReleased) { gamePaused = keyReleased2 = false; SDL_SetCursor(inputs.arrow); }
			if (hEvents.type == SDL_KEYUP && !gamePaused) { if (hEvents.key.keysym.sym == SDLK_ESCAPE || hEvents.key.keysym.sym == SDLK_p) { keyReleased2 = true; inputs.selected = false; } }
		}
		hCollision->ballCollisionCheck(gamePaused);
		inputs.keyboardEvents(singlePlayer, gamePaused);
		if (singlePlayer) { hAI->aiBehavior(singlePlayer, gamePaused); }
		if (hCollision->leftPoints == 5 && !gameOverTextDisplayed)
		{
			singlePlayer ?
				hCollision->Text["gameOver"].loadText("assets/Hakugyokurou.ttf", "Congrats, you won!", { 255, 255, 255 }, 40.0f)
				: hCollision->Text["gameOver"].loadText("assets/Hakugyokurou.ttf", "Player 1 Wins!", { 255, 255, 255 }, 40.0f);
			texture->Textures["ball"]->setPos(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
			gameOver = gameOverTextDisplayed = gamePaused = true;
		}
		if (hCollision->rightPoints == 5 && !gameOverTextDisplayed)
		{
			singlePlayer ?
				hCollision->Text["gameOver"].loadText("assets/Hakugyokurou.ttf", "Computer has won!", { 255, 255, 255 }, 40.0f)
				: hCollision->Text["gameOver"].loadText("assets/Hakugyokurou.ttf", "Player 2 Wins!", { 255, 255, 255 }, 40.0f);
			texture->Textures["ball"]->setPos(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
			gameOver = gameOverTextDisplayed = gamePaused = true;
		}
		texture->Textures["ball"]->moving = false;
		if (timer.getInstanceTime() <= 35)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "3", { 155, 255, 155 }, 70.0f);
			if (!soundPlayed3) { Mix_PlayChannel(-1, countDown, 0); soundPlayed3 = true; }
		}
		if (timer.getInstanceTime() <= 70 && timer.getInstanceTime() > 35)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "2", { 255, 255, 155 }, 70.0f);
			if (!soundPlayed2) { Mix_PlayChannel(-1, countDown, 0); soundPlayed2 = true; }
		}
		if (timer.getInstanceTime() <= 105 && timer.getInstanceTime() > 70)
		{
			hCollision->Text["countDown"].loadText("assets/Hakugyokurou.ttf", "1", { 255, 155, 155 }, 70.0f);
			if (!soundPlayed1) { Mix_PlayChannel(-1, countDown, 0); soundPlayed1 = true; }
		}
		if (timer.getInstanceTime() > 105 && !gamePaused)
		{
			SDL_DestroyTexture(hCollision->Text["countDown"].textTexture);
			texture->Textures["ball"]->translate(Vector2(-8.5f, 0.0f));
		}
		hGraphics->clearBuffer();
		texture->Textures["playerPaddleTop"]->renderTexture(9, 21);
		texture->Textures["playerPaddleMiddle"]->renderTexture(9, 13);
		texture->Textures["playerPaddleBottom"]->renderTexture(9, 21);
		texture->Textures["opponentPaddleTop"]->renderTexture(9, 21);
		texture->Textures["opponentPaddleMiddle"]->renderTexture(9, 13);
		texture->Textures["opponentPaddleBottom"]->renderTexture(9, 21);
		texture->Textures["ball"]->renderTexture(texture->getCircleCollider().r, texture->getCircleCollider().r);
		for (int i = 0; i < 27; i++)
		{
			mid = { (hGraphics->getWindowWidth() / 2.0f) - 1.0f, i * 20.0f, 2.0f, 10.0f };
			SDL_RenderCopyF(hGraphics->getRenderer(), texture->Textures["middleLine"]->getTexture(), NULL, &mid);
		}
		texture->Textures["topBoundary"]->renderTexture(hGraphics->getWindowWidth(), 20);
		texture->Textures["bottomBoundary"]->renderTexture(hGraphics->getWindowWidth(), 20);
		texture->Textures["topBoundaryCheck"]->renderTexture(hGraphics->getWindowWidth(), 12);
		texture->Textures["bottomBoundaryCheck"]->renderTexture(hGraphics->getWindowWidth(), 12);
		texture->Textures["leftBoundary"]->renderTexture(20, hGraphics->getWindowHeight() + 100);
		texture->Textures["rightBoundary"]->renderTexture(20, hGraphics->getWindowHeight() + 100);
		ballTrail.renderTrail(100);
		leftPaddleTrail.renderTrail(80);
		rightPaddleTrail.renderTrail(100);

		hCollision->Text["avgFpsText"].renderText(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() - 10);
		hCollision->Text["fpsText"].renderText(hGraphics->getWindowWidth() - 12, hGraphics->getWindowHeight() - 10);
		hCollision->Text["playerPoints"].renderText(hGraphics->getWindowWidth() / 2 - 74, 70);
		hCollision->Text["opponentPoints"].renderText(hGraphics->getWindowWidth() / 2 + 86, 70);
		hCollision->Text["countDown"].renderText(hGraphics->getWindowWidth() / 2, hGraphics->getWindowHeight() / 2);

		if (singlePlayer) { hAI->aiBehavior(singlePlayer, gamePaused); }
		if (gamePaused) { pauseScreen(); }
		if (singlePlayer && timer.getInstanceTime() < 105)
		{
			hCollision->Text["instructions"].renderText(hGraphics->getWindowWidth() / 2 - 200, hGraphics->getWindowHeight() / 2);
		}
		if (!singlePlayer && timer.getInstanceTime() < 105)
		{
			hCollision->Text["instructions"].renderText(hGraphics->getWindowWidth() / 2 - 200, hGraphics->getWindowHeight() / 2);
			hCollision->Text["instructions2"].renderText(hGraphics->getWindowWidth() / 2 + 200, hGraphics->getWindowHeight() / 2);
		}
		if (gameOver) 
		{ 
			hCollision->Text["gameOver"].renderText(hGraphics->getWindowWidth() / 2, 130); 
			hCollision->Text["gameOver()"].renderText(hGraphics->getWindowWidth() / 2, 160);
		}
		hGraphics->render();

		//std::cout << "Total memory usage: " << TotalAllocated - TotalFreed << "\n";
		SDL_DestroyTexture(hCollision->Text["avgFpsText"].textTexture);

		frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS)) { SDL_Delay((1000.0f / FPS) - frameTicks); }
	}
}

void Game::pauseScreen()
{
	if (!pauseTextsLoaded || inputs.changeOptimizer < 2 && inputs.changeOptimizer2 < 2 || inputs.changeOptimizer3 < 2 && inputs.changeOptimizer4 < 2)
	{
		hCollision->Text["pauseReset"].loadText("assets/Hakugyokurou.ttf", "Reset (r)", inputs.ResetColor, 50.0f);
		hCollision->Text["pauseExit"].loadText("assets/Hakugyokurou.ttf", "Exit (e)", inputs.ExitColor, 50.0f);
		pauseTextsLoaded = true;
	}
	hCollision->Text["pauseReset"].renderText(hGraphics->getWindowWidth() / 2, 225);
	hCollision->Text["pauseExit"].renderText(hGraphics->getWindowWidth() / 2, 300);
	switch (inputs.gamePauseEvents(&hEvents))
	{
	case 1: hCollision->leftPoints = 0;  hCollision->rightPoints = 0;
		hCollision->leftScore.str(""); hCollision->rightScore.str("");
		hCollision->leftScore << hCollision->leftPoints;	hCollision->rightScore << hCollision->rightPoints;
		hCollision->Text["playerPoints"].loadText("assets/bit5x3.ttf", hCollision->leftScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		hCollision->Text["opponentPoints"].loadText("assets/bit5x3.ttf", hCollision->rightScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		texture->Textures["ball"]->setPos(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
		texture->Textures["ball"]->speed = { 1.0f, 1.0f };
		texture->Textures["playerPaddleMiddle"]->setPos(Vector2(40, hGraphics->getWindowHeight() / 2));
		texture->Textures["opponentPaddleMiddle"]->setPos(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2));
		std::srand(std::time(NULL)); oddOrEven = rand() % 2;
		oddOrEven < 1 ? texture->Textures["ball"]->rotate(180) : texture->Textures["ball"]->rotate(0);
		hCollision->bouncedPlayer = hCollision->bouncedOpponent = hCollision->bouncedBottom = hCollision->bouncedTop = hCollision->bouncedBottomCheck = 
		hCollision->bouncedTopCheck = hCollision->touchedLeft = hCollision->touchedRight = hCollision->scored = 
		gamePaused = gameOver = gameOverTextDisplayed = soundPlayed3 = soundPlayed2 = soundPlayed1 = false;
		timer.resetInstance(); hCollision->timer->resetInstance();  break;
	case 2:	hCollision->leftPoints = 0;  hCollision->rightPoints = 0;
		hCollision->leftScore.str("");	hCollision->rightScore.str("");
		hCollision->leftScore << hCollision->leftPoints;	hCollision->rightScore << hCollision->rightPoints;
		hCollision->Text["playerPoints"].loadText("assets/bit5x3.ttf", hCollision->leftScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		hCollision->Text["opponentPoints"].loadText("assets/bit5x3.ttf", hCollision->rightScore.str().c_str(), { 255, 255, 255 }, 100.0f);
		texture->Textures["ball"]->setPos(Vector2(texture->getCircleCollider().x, texture->getCircleCollider().y));
		texture->Textures["ball"]->speed = { 1.0f, 1.0f };
		texture->Textures["playerPaddleMiddle"]->setPos(Vector2(40, hGraphics->getWindowHeight() / 2));
		texture->Textures["opponentPaddleMiddle"]->setPos(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2));
		std::srand(std::time(NULL)); oddOrEven = rand() % 2;
		oddOrEven < 1 ? texture->Textures["ball"]->rotate(180) : texture->Textures["ball"]->rotate(0);
		hCollision->bouncedPlayer = hCollision->bouncedOpponent = hCollision->bouncedBottom = hCollision->bouncedTop = 
		hCollision->bouncedBottomCheck = hCollision->bouncedTopCheck = hCollision->touchedLeft = hCollision->touchedRight = hCollision->scored = 
		hQuitTitle = gamePaused = gameOver = gameOverTextDisplayed = soundPlayed3 = soundPlayed2 = soundPlayed1 = false;  hQuitGame = true;
		timer.resetInstance(); hCollision->timer->resetInstance(); break;
	}
}