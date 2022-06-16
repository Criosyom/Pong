#include "Inputs.h"


Inputs::Inputs() 
{ 
    hCollision = Collision::instance();
    texture = texture->instance();
    currentKeyStates = SDL_GetKeyboardState(NULL); 
}
Inputs::~Inputs() {}

void Inputs::keyboardEvents(bool isSingle) // me = true;
{
    bool collidedTop = SDL_HasIntersectionF(texture->Textures["playerPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect());
    bool collidedBottom = SDL_HasIntersectionF(texture->Textures["playerPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect());
    bool collidedTop2 = SDL_HasIntersectionF(texture->Textures["opponentPaddleTop"]->getDestRect(), texture->Textures["topBoundary"]->getDestRect());
    bool collidedBottom2 = SDL_HasIntersectionF(texture->Textures["opponentPaddleBottom"]->getDestRect(), texture->Textures["bottomBoundary"]->getDestRect());
    if (isSingle)
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
    if (currentKeyStates[SDL_SCANCODE_ESCAPE] || currentKeyStates[SDL_SCANCODE_P])
    {
        std::cout << "Bro that's cringe\n";
    }
}

int Inputs::mouseEvents(SDL_Event* e)
{
    SDL_Cursor* clickHand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    if (e->type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&x, &y);
    }
    if (x < hCollision->Text["Polyvinyl Chloride"].dst.x + hCollision->Text["Polyvinyl Chloride"].dst.w && x > hCollision->Text["Polyvinyl Chloride"].dst.x
        && y < hCollision->Text["Polyvinyl Chloride"].dst.y + hCollision->Text["Polyvinyl Chloride"].dst.h && y > hCollision->Text["Polyvinyl Chloride"].dst.y)
    {
        PVCColor = { 99, 123, 223 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            return 1;
        }
    }
    else 
    { 
        PVCColor = { 255, 255, 255 }; 
    }
    if (x < hCollision->Text["PVP"].dst.x + hCollision->Text["PVP"].dst.w && x > hCollision->Text["PVP"].dst.x
        && y < hCollision->Text["PVP"].dst.y + hCollision->Text["PVP"].dst.h && y > hCollision->Text["PVP"].dst.y)
    {
        PVPColor = { 49, 223, 100 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            return 2;
        }
    }
    else
    {
        PVPColor = { 255, 255, 255 };
    }
    if (x < hCollision->Text["SPEED"].dst.x + hCollision->Text["SPEED"].dst.w && x > hCollision->Text["SPEED"].dst.x
        && y < hCollision->Text["SPEED"].dst.y + hCollision->Text["SPEED"].dst.h && y > hCollision->Text["SPEED"].dst.y)
    {
        SPEEDColor = { 239, 223, 23 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            return 3;
        }
    }
    else
    {
        SPEEDColor = { 255, 255, 255 };
    }
    if (x < hCollision->Text["ExitGame"].dst.x + hCollision->Text["ExitGame"].dst.w && x > hCollision->Text["ExitGame"].dst.x
        && y < hCollision->Text["ExitGame"].dst.y + hCollision->Text["ExitGame"].dst.h && y > hCollision->Text["ExitGame"].dst.y)
    {
        ExitColor = { 230, 23, 42 };
        SDL_SetCursor(clickHand);
        if (!selected) { Mix_PlayChannel(-1, hCollision->selectSound, 0); selected = true; }
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_SetCursor(arrow);
            return 4;
        }
    }
    else
    {
        ExitColor = { 255, 255, 255 };
    }

    // Please ignore this absurdity
    if (!(x < hCollision->Text["Polyvinyl Chloride"].dst.x + hCollision->Text["Polyvinyl Chloride"].dst.w && x > hCollision->Text["Polyvinyl Chloride"].dst.x
        && y < hCollision->Text["Polyvinyl Chloride"].dst.y + hCollision->Text["Polyvinyl Chloride"].dst.h && y > hCollision->Text["Polyvinyl Chloride"].dst.y ||
        x < hCollision->Text["PVP"].dst.x + hCollision->Text["PVP"].dst.w && x > hCollision->Text["PVP"].dst.x
        && y < hCollision->Text["PVP"].dst.y + hCollision->Text["PVP"].dst.h && y > hCollision->Text["PVP"].dst.y ||
        x < hCollision->Text["SPEED"].dst.x + hCollision->Text["SPEED"].dst.w && x > hCollision->Text["SPEED"].dst.x
        && y < hCollision->Text["SPEED"].dst.y + hCollision->Text["SPEED"].dst.h && y > hCollision->Text["SPEED"].dst.y ||
        x < hCollision->Text["ExitGame"].dst.x + hCollision->Text["ExitGame"].dst.w && x > hCollision->Text["ExitGame"].dst.x
        && y < hCollision->Text["ExitGame"].dst.y + hCollision->Text["ExitGame"].dst.h && y > hCollision->Text["ExitGame"].dst.y))
    {
        SDL_SetCursor(arrow);
        selected = false;
    }
}