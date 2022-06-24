#include "Inputs.h"


Inputs::Inputs() 
{ 
    hCollision = Collision::instance();
    texture = texture->instance();
    currentKeyStates = SDL_GetKeyboardState(NULL); 
}
Inputs::~Inputs() {}

void Inputs::titleKeyBoardEvents(SDL_Event* e)
{
    Mix_VolumeMusic(35);
    if (e->type == SDL_KEYUP) { if (e->key.keysym.sym == SDLK_e) { eirin = true; } }
    if (currentKeyStates[SDL_SCANCODE_9])
    {
        texture->Textures["titleBall"]->loadTexture("assets/cirnoFumo.png");
        titleBallWidth = 160; titleBallHeight = 160;
        musicSwitched = true;
    }

    if (currentKeyStates[SDL_SCANCODE_A])
    {
        texture->Textures["titleBall"]->loadTexture("assets/ayaFumo.png");
        titleBallWidth = 150; titleBallHeight = 190;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_B])
    {
        texture->Textures["titleBall"]->loadTexture("assets/byakurenFumo.png");
        titleBallWidth = 140; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_C])
    {
        texture->Textures["titleBall"]->loadTexture("assets/chimataFumo.png");
        titleBallWidth = 130; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        texture->Textures["titleBall"]->loadTexture("assets/aliceFumo.png");
        titleBallWidth = 160; titleBallHeight = 160;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_E] && eirin)
    {
        texture->Textures["titleBall"]->loadTexture("assets/eirinFumo.png");
        titleBallWidth = 120; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_F])
    {
        texture->Textures["titleBall"]->loadTexture("assets/flandreFumo.png");
        titleBallWidth = 150; titleBallHeight = 150;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_G])
    {
        texture->Textures["titleBall"]->loadTexture("assets/youmuFumo.png");
        titleBallWidth = 160; titleBallHeight = 160;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_H])
    {
        texture->Textures["titleBall"]->loadTexture("assets/koishiFumo.png");
        titleBallWidth = 180; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_I])
    {
        texture->Textures["titleBall"]->loadTexture("assets/mokouFumo.png");
        titleBallWidth = 160; titleBallHeight = 150;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_J])
    {
        texture->Textures["titleBall"]->loadTexture("assets/joonAndShionFumo.png");
        titleBallWidth = 260; titleBallHeight = 190;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_K])
    {
        texture->Textures["titleBall"]->loadTexture("assets/keikiFumo.png");
        titleBallWidth = 150; titleBallHeight = 160;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_L])
    {
        texture->Textures["titleBall"]->loadTexture("assets/sumirekoFumo.png");
        titleBallWidth = 150; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_M])
    {
        texture->Textures["titleBall"]->loadTexture("assets/marisaFumo.png");
        titleBallWidth = 160; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_N])
    {
        texture->Textures["titleBall"]->loadTexture("assets/suwakoFumo.png");
        titleBallWidth = 160; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_O])
    {
        texture->Textures["titleBall"]->loadTexture("assets/okinaFumo.png");
        titleBallWidth = 150; titleBallHeight = 190;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_P])
    {
        texture->Textures["titleBall"]->loadTexture("assets/prismriverSistersFumo.png");
        titleBallWidth = 330; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_Q])
    {
        texture->Textures["titleBall"]->loadTexture("assets/shinmyoumaruFumo.png");
        titleBallWidth = 70; titleBallHeight = 70;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_R])
    {
        texture->Textures["titleBall"]->loadTexture("assets/reimuFumo.png");
        titleBallWidth = 150; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        texture->Textures["titleBall"]->loadTexture("assets/sakuyaFumo.png");
        titleBallWidth = 150; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_T])
    {
        texture->Textures["titleBall"]->loadTexture("assets/tenshiFumo.png");
        titleBallWidth = 160; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_U])
    {
        texture->Textures["titleBall"]->loadTexture("assets/reisenFumo.png");
        titleBallWidth = 150; titleBallHeight = 190;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_V])
    {
        texture->Textures["titleBall"]->loadTexture("assets/remiliaFumo.png");
        titleBallWidth = 170; titleBallHeight = 170;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        texture->Textures["titleBall"]->loadTexture("assets/yuyukoFumo.png");
        titleBallWidth = 150; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_X])
    {
        texture->Textures["titleBall"]->loadTexture("assets/junkoFumo.png");
        titleBallWidth = 170; titleBallHeight = 190;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_Y])
    {
        texture->Textures["titleBall"]->loadTexture("assets/yukariFumo.png");
        titleBallWidth = 140; titleBallHeight = 180;
        musicSwitched = true;
    }
    if (currentKeyStates[SDL_SCANCODE_Z])
    {
        texture->Textures["titleBall"]->loadTexture("assets/ZUN.png");
        titleBallWidth = 300; titleBallHeight = 330;
        musicSwitched = pog = true;
    }
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        musicStop = true;
        texture->Textures["titleBall"]->loadTexture("assets/ballWhite.png");
        titleBallWidth = 12; titleBallHeight = 12;
    }
    if (musicSwitched)
    {
        titleBallSpeed = 6;
        !pog ? hCollision->Text["PONG"].loadText("assets/BlippoBold.ttf", "FUMO", { 255, 255, 255 }, 125.0f) 
        : hCollision->Text["PONG"].loadText("assets/BlippoBold.ttf", "POG", { 255, 255, 255 }, 125.0f);
        hCollision->Text["spaceToStop"].loadText("assets/SunflowerHighway.otf", "Press space to stop this madness", { 255, 255, 255 }, 15.0f);
        pog = pong = musicSwitched = musicStop = false;
    }
    if (musicStop) 
    {
        titleBallSpeed = 12; pog = false; 
        if (!pong) { hCollision->Text["PONG"].loadText("assets/BlippoBold.ttf", "PONG", { 255, 255, 255 }, 125.0f); pong = true; }
    }
}

void Inputs::keyboardEvents(bool isSingle, bool isGamePaused)
{
    texture->Textures["playerPaddleMiddle"]->moving = false;
    if (!isGamePaused)
    {
        bool collidedTop = SDL_HasIntersectionF(texture->Textures["playerPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect());
        bool collidedBottom = SDL_HasIntersectionF(texture->Textures["playerPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect());
        bool collidedTop2 = SDL_HasIntersectionF(texture->Textures["opponentPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect());
        bool collidedBottom2 = SDL_HasIntersectionF(texture->Textures["opponentPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect());
        if (isSingle)   // me = true;
        {
            if (currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_S] && !collidedTop || currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_DOWN] && !collidedTop)
            {
                texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, -7.0f));
            }
            if (currentKeyStates[SDL_SCANCODE_S] && !collidedBottom || currentKeyStates[SDL_SCANCODE_DOWN] && !collidedBottom)
            {
                texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, 7.0f));
            }
        }
        else
        {
            if (currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_S] && !collidedTop)
            {
                texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, -7.0f));
            }
            if (currentKeyStates[SDL_SCANCODE_S] && !collidedBottom)
            {
                texture->Textures["playerPaddleMiddle"]->translate(Vector2(0.0f, 7.0f));
            }
            if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_DOWN] && !collidedTop2)
            {
                texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, -7.0f));
            }
            if (currentKeyStates[SDL_SCANCODE_DOWN] && !collidedBottom2)
            {
                texture->Textures["opponentPaddleMiddle"]->translate(Vector2(0.0f, 7.0f));
            }
        }
    }
}

int Inputs::mouseEvents(SDL_Event* e)
{
    clickHand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    if (e->type == SDL_MOUSEMOTION) { SDL_GetMouseState(&x, &y); }
    if (x < hCollision->Text["Polyvinyl Chloride"].dst.x + hCollision->Text["Polyvinyl Chloride"].dst.w && x > hCollision->Text["Polyvinyl Chloride"].dst.x
        && y < hCollision->Text["Polyvinyl Chloride"].dst.y + hCollision->Text["Polyvinyl Chloride"].dst.h && y > hCollision->Text["Polyvinyl Chloride"].dst.y)
    {
        PVCColor = { 99, 123, 223 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        titleOptimizer++; titleOptimizer2 = 0;
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            selected = false;
            return 1;
        }
    }
    else 
    { 
        titleOptimizer = 0; titleOptimizer2++;
        PVCColor = { 255, 255, 255 }; 
    }
    if (x < hCollision->Text["PVP"].dst.x + hCollision->Text["PVP"].dst.w && x > hCollision->Text["PVP"].dst.x
        && y < hCollision->Text["PVP"].dst.y + hCollision->Text["PVP"].dst.h && y > hCollision->Text["PVP"].dst.y)
    {
        PVPColor = { 49, 223, 100 };
        SDL_SetCursor(clickHand);
        titleOptimizer3++; titleOptimizer4 = 0;
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            selected = false;
            return 2;
        }
    }
    else
    {
        titleOptimizer3 = 0; titleOptimizer4++;
        PVPColor = { 255, 255, 255 };
    }
    if (x < hCollision->Text["QuitGame"].dst.x + hCollision->Text["QuitGame"].dst.w && x > hCollision->Text["QuitGame"].dst.x
        && y < hCollision->Text["QuitGame"].dst.y + hCollision->Text["QuitGame"].dst.h && y > hCollision->Text["QuitGame"].dst.y)
    {
        QuitColor = { 230, 23, 42 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        titleOptimizer5++; titleOptimizer6 = 0;
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            selected = false;
            return 3;
        }
    }
    else
    {
        titleOptimizer5 = 0; titleOptimizer6++;
        QuitColor = { 255, 255, 255 };
    }

    // Please ignore this absurdity
    if (!(x < hCollision->Text["Polyvinyl Chloride"].dst.x + hCollision->Text["Polyvinyl Chloride"].dst.w && x > hCollision->Text["Polyvinyl Chloride"].dst.x
        && y < hCollision->Text["Polyvinyl Chloride"].dst.y + hCollision->Text["Polyvinyl Chloride"].dst.h && y > hCollision->Text["Polyvinyl Chloride"].dst.y ||
        x < hCollision->Text["PVP"].dst.x + hCollision->Text["PVP"].dst.w && x > hCollision->Text["PVP"].dst.x
        && y < hCollision->Text["PVP"].dst.y + hCollision->Text["PVP"].dst.h && y > hCollision->Text["PVP"].dst.y ||
        x < hCollision->Text["SPEED"].dst.x + hCollision->Text["SPEED"].dst.w && x > hCollision->Text["SPEED"].dst.x
        && y < hCollision->Text["SPEED"].dst.y + hCollision->Text["SPEED"].dst.h && y > hCollision->Text["SPEED"].dst.y ||
        x < hCollision->Text["QuitGame"].dst.x + hCollision->Text["QuitGame"].dst.w && x > hCollision->Text["QuitGame"].dst.x
        && y < hCollision->Text["QuitGame"].dst.y + hCollision->Text["QuitGame"].dst.h && y > hCollision->Text["QuitGame"].dst.y))
    {
        SDL_SetCursor(arrow);
        selected = false;
    }
}

int Inputs::gamePauseEvents(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION) { SDL_GetMouseState(&x, &y); }
    if (x < hCollision->Text["pauseReset"].dst.x + hCollision->Text["pauseReset"].dst.w && x > hCollision->Text["pauseReset"].dst.x
        && y < hCollision->Text["pauseReset"].dst.y + hCollision->Text["pauseReset"].dst.h && y > hCollision->Text["pauseReset"].dst.y)
    {
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        ResetColor = { 180, 180, 180 };
        SDL_SetCursor(clickHand); changeOptimizer++; changeOptimizer2 = 0;
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            selected = false;
            return 1;
        }
       
    }
    else { changeOptimizer = 0; changeOptimizer2++; ResetColor = { 255, 255, 255 }; }
    if (x < hCollision->Text["pauseExit"].dst.x + hCollision->Text["pauseExit"].dst.w && x > hCollision->Text["pauseExit"].dst.x
        && y < hCollision->Text["pauseExit"].dst.y + hCollision->Text["pauseExit"].dst.h && y > hCollision->Text["pauseExit"].dst.y)
    {
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        ExitColor = { 180, 180, 180 };	
        SDL_SetCursor(clickHand); changeOptimizer3++; changeOptimizer4 = 0;
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            selected = false;
            return 2;
        }
    }
    else { changeOptimizer3 = 0; changeOptimizer4++; ExitColor = { 255, 255, 255 }; }
    if (!(x < hCollision->Text["pauseReset"].dst.x + hCollision->Text["pauseReset"].dst.w && x > hCollision->Text["pauseReset"].dst.x
        && y < hCollision->Text["pauseReset"].dst.y + hCollision->Text["pauseReset"].dst.h && y > hCollision->Text["pauseReset"].dst.y ||
        x < hCollision->Text["pauseExit"].dst.x + hCollision->Text["pauseExit"].dst.w && x > hCollision->Text["pauseExit"].dst.x
        && y < hCollision->Text["pauseExit"].dst.y + hCollision->Text["pauseExit"].dst.h && y > hCollision->Text["pauseExit"].dst.y))
    {
        SDL_SetCursor(arrow);
        selected = false;
    }
    if (currentKeyStates[SDL_SCANCODE_R]) { SDL_SetCursor(arrow); selected = false; return 1; }
    if (currentKeyStates[SDL_SCANCODE_E]) { SDL_SetCursor(arrow); selected = eirin = false; return 2; }
}