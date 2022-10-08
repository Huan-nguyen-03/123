#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Texture.h"

#include <iostream>
#include <vector>

using namespace std;

class Explosion : public Texture
{
public:
    Explosion();
    ~Explosion();
    void loadExplosion(SDL_Renderer * renderer);
    void show(SDL_Renderer * renderer, int i);

    void setX(int i);
    void setY(int i);

protected:
    int count_explosion;
    int x_exp;
    int y_exp;
private:
};