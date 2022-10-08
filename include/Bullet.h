#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Texture.h"
#include "Constant.h"
#include "Sound.h"

class Bullet : public Texture
{
public:
    Bullet();
    ~Bullet();
    void loadBullet(SDL_Renderer * renderer);
    void handleEvent(SDL_Event e, int & eventRepeat, bool & fire);
    //void showBullet (SDL_Renderer* renderer, int x, int y, int status);
    void showBullet (SDL_Renderer* renderer, int x, int y, bool & check_fly, int status);

    void loadAngle(SDL_Renderer * renderer);
    void showAngle(SDL_Renderer * renderer, int x, int y);     
    void showImageAngle(SDL_Renderer * renderer, int x, int y, bool status);

    void loadForce(SDL_Renderer * renderer);
    void showForce(SDL_Renderer * renderer, int x, int y);
    
    void loadForceBar(SDL_Renderer * renderer);
    void showForceBar(SDL_Renderer * renderer, int x, int y);
    int getAngle();
    int getForce();
protected:
    int angle;
    int force;

    Uint32 startTime;
    Uint32 endTime;

    Sound sound;
private:
    bool holdSpace;
};

