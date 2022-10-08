#pragma once

#include "SDL2/SDL.h"
#include "Constant.h"
#include "Texture.h"
#include "Sound.h"

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Figure : public Texture
{
public:
    Figure(int x_begin = 100);
    ~Figure();



    
    void loadMedia(SDL_Renderer * renderer);
    void handleEvent(SDL_Event e, int &status);
    void showFigure(SDL_Renderer * renderer,  int &status);
    void showFigureFire(SDL_Renderer * renderer,  int &status, int cnt);

    void loadHP(SDL_Renderer * renderer);
    void showHP(SDL_Renderer * renderer, int x, int y);

    bool checkHit(int explosion_pos, int status);
    void minusHP(int explosion_pos, int status);

    int getHP();

    void setCountFigure(int i);
    void showDead_F(SDL_Renderer * renderer, int x, int y);
    void reset(int hp, int pos);

    void loadMinusHP(SDL_Renderer * renderer);
    void showMinusHP(SDL_Renderer * renderer, int x, int y);
protected:
    int count_figure;
    int hp;
    int dame;
    Sound sound;
    

private:


};