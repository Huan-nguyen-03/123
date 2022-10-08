#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "Constant.h"
#include "Map.h"
#include "Texture.h"
#include "Figure.h"
#include "Bullet.h"
#include "Explosion.h"


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

class MainControl
{
public:
    MainControl();
    ~MainControl();
    void logSDLError(ostream& os, const string &msg, bool fatal = false);
    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
    void waitUntilKeyPressed();
    void close();

    void run();

    void showTrajectory(int angle, int force, int & dx, int x, int y, int &status);
    void showAllExplosion();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;


protected:
private:
    SDL_Window * window;
    SDL_Renderer * renderer;

    Map map;
    Figure figure;
    Bullet bullet;
    Explosion explosion;
    

    bool end_loop;
    bool fire;
    SDL_Event e;
    int eventRepeat;
    int status;
    bool checkCol;

    int dx;
    int cnt_figure;    // used to set the image when firing
    int cnt_explosion;
};
