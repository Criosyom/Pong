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
	Textures["playerPaddle"] = new Texture(Vector2(30, hGraphics->getWindowHeight() / 2 - 25));
	Textures["opponentPaddle"] = new Texture(Vector2(hGraphics->getWindowWidth() - 40, hGraphics->getWindowHeight() / 2 - 25));
	Textures["middleLine"] = new Texture();
	Textures["ball"] = new Texture(Vector2(hGraphics->getWindowWidth() / 2 - 11, hGraphics->getWindowHeight() / 2 - 10));
	Textures["upperBorder"] = new Texture(Vector2(0.0f, -6.0f));
	Textures["lowerBorder"] = new Texture(Vector2(0.0f, hGraphics->getWindowHeight()));

	Textures["playerPaddle"]->loadTexture("assets/pads.png");
	Textures["opponentPaddle"]->loadTexture("assets/pads.png");
	Textures["middleLine"]->loadTexture("assets/pads.png");
	Textures["ball"]->loadTexture("assets/ball.png");
	Textures["upperBorder"]->loadTexture("assets/pads.png");
	Textures["lowerBorder"]->loadTexture("assets/pads.png");


	for (std::pair<std::string, Texture*> t : Textures)
	{
		
	}

	Text["fpsText"].loadText("assets/Hakugyokurou.ttf", "fps", { 255, 255, 255 }, 14.0f);

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
		Text["avgFpsText"].loadText("assets/Hakugyokurou.ttf", stream.str().c_str(), {255, 255, 255}, 14.0f);

		bool collidedUpper = SDL_HasIntersection(Textures["playerPaddle"]->getDestRect(), Textures["upperBorder"]->getDestRect());
		bool collidedLower = SDL_HasIntersection(Textures["playerPaddle"]->getDestRect(), Textures["lowerBorder"]->getDestRect());
		if (inputs.currentKeyStates[SDL_SCANCODE_W] && !inputs.currentKeyStates[SDL_SCANCODE_S] && !collidedUpper)
		{
			Textures["playerPaddle"]->translate(Vector2(0.0f, -7.0f));
			Textures["opponentPaddle"]->translate(Vector2(0.0f, -7.0f));
		}
		if (inputs.currentKeyStates[SDL_SCANCODE_S] && !collidedLower)
		{
			Textures["playerPaddle"]->translate(Vector2(0.0f, 7.0f));
			Textures["opponentPaddle"]->translate(Vector2(0.0f, 7.0f));
		}

		Textures["ball"]->translate(Vector2(5.0f, 2.0f));
		if (SDL_HasIntersection(Textures["ball"]->getDestRect(), Textures["playerPaddle"]->getDestRect()) && !q)
		{
			Textures["ball"]->speed = Textures["ball"]->speed * Vector2{-1.1f, 1.01f};
			q = true;
			w = e = r = false;
		}
		if (SDL_HasIntersection(Textures["ball"]->getDestRect(), Textures["opponentPaddle"]->getDestRect()) && !w)
		{
			Textures["ball"]->speed = Textures["ball"]->speed * Vector2{ -1.1f, 1.01f };
			w = true;
			q = e = r = false;
		}
		if (SDL_HasIntersection(Textures["ball"]->getDestRect(), Textures["lowerBorder"]->getDestRect()) && !e)
		{
			Textures["ball"]->speed = Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };
			e = true;
			r = false;

		}
		if (SDL_HasIntersection(Textures["ball"]->getDestRect(), Textures["upperBorder"]->getDestRect()) && !r)
		{
			Textures["ball"]->speed = Textures["ball"]->speed * Vector2{ 1.0f, -1.0f };

			r = true;
			e = false;
		}


		hGraphics->clearBuffer();

		Textures["playerPaddle"]->renderTexture(10, 50);
		Textures["opponentPaddle"]->renderTexture(10, 50);
		Textures["ball"]->renderTexture(19, 17);
		for (int i = 0; i < 27; i++)
		{
			SDL_Rect mid;
			mid.x = (hGraphics->getWindowWidth() / 2) - 1;
			mid.y = i * 20;
			mid.w = 2;
			mid.h = 10;
			SDL_RenderCopy(hGraphics->getRenderer(), Textures["middleLine"]->getTexture(), NULL, &mid);
		}
		Textures["upperBorder"]->renderTexture(hGraphics->getWindowWidth(), 6);
		Textures["lowerBorder"]->renderTexture(hGraphics->getWindowWidth(), 6);

		Text["avgFpsText"].renderText(hGraphics->getWindowWidth() - 50, hGraphics->getWindowHeight() - 15);
		Text["fpsText"].renderText(hGraphics->getWindowWidth() - 22, hGraphics->getWindowHeight() - 15);
		hGraphics->render();

		float frameTicks = timer.getDeltaTime();
		++countedFrames;
		if (frameTicks < (1000.0f / FPS))
		{
			SDL_Delay((1000.0f/FPS) - frameTicks);
		}
	}
}



