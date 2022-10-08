#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Texture.h"
#include "Constant.h"

class Bullet : public Texture
{
public:
    Bullet();
    ~Bullet();
    void loadBullet(SDL_Renderer * renderer);
    void handleEvent(SDL_Event e, int & eventRepeat, bool & fire);
    //void showBullet (SDL_Renderer* renderer, int x, int y, int status);
    void showBullet (SDL_Renderer* renderer, int x, int y);

    int getAngle();
    int getForce();
protected:
    int angle;
    int force;

    Uint32 startTime;
    Uint32 endTime;


private:
};

