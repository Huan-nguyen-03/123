#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "Texture.h"

using namespace std;

class Fly : public Texture
{
public:
    Fly();
    ~Fly();
    void loadFly(SDL_Renderer * renderer);
    void handleEvent(SDL_Event e, bool &check_fly, int x, int y);
    void showFly(int x, int y, SDL_Renderer * renderer, bool &check_fly);
protected:
private:
};