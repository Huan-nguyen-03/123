#include "Fly.h"

using namespace std;

Fly::Fly()
{

}

Fly :: ~Fly()
{

}

void Fly:: loadFly(SDL_Renderer * renderer)
{
    loadFromFile("images/fly.png", renderer);
    loadFromFile("images/fly.png", renderer);          // blurred image
    setBlendMode(1, SDL_BLENDMODE_BLEND);
    setAlpha(1, 50);
}

void Fly:: handleEvent(SDL_Event e, bool &check_fly, int x, int y)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.x >=x && e.button.y >= y && e.button.x <= x+75 && e.button.y <=y+75 )
            check_fly = true;
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f)
        check_fly = true;
}

void Fly:: showFly(int x, int y, SDL_Renderer * renderer, bool &check_fly)
{
    if (!check_fly)
        renderTexture(0, renderer, x, y);
    else
    {
        renderTexture(1, renderer, x, y);
    }

    
}