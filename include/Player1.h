#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "Map.h"
#include "Figure.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Constant.h"
#include "Fly.h"
#include "Sound.h"
#include "TurnImage.h"

#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

class Player1
{
public:
    Player1();
    ~Player1();

    

    void loadMedia(SDL_Renderer * renderer);
    void handleEvent(SDL_Event &e, bool & turn);
    void show(SDL_Renderer * renderer, int explosion_pos, bool &otherMinus, bool turn, int &convertTurn);


    void showTrajectory(SDL_Renderer * renderer,int angle, int force, int & dx, int x, int y, int &status, int &convertTurn);
    void showAllExplosion(SDL_Renderer * renderer, int &convertTurn);

    int getPositionExplosion();
    bool getMinus();
    bool checkDead();
    void showDead(SDL_Renderer * renderer);
    void resetPlayer();




    bool minus;
protected:
    Figure figure;
    Bullet bullet;
    Explosion explosion;
    //Map map;
    Fly fly;
    Sound sound;
    TurnImage turnImage;

    bool fire;
    int eventRepeat;
    int status;
    bool checkCol;

    int dx;
    double t; // time;
    int cnt_figure;    // used to set the image when firing
    int cnt_explosion;
    bool check_fly;
    
    
private:
};


