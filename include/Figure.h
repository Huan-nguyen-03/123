#pragma once

#include "SDL2/SDL.h"
#include "Constant.h"
#include "Texture.h"

#include <iostream>

using namespace std;

class Figure : public Texture
{
public:
    Figure();
    ~Figure();
    
    void loadMedia(SDL_Renderer * renderer);
    void handleEvent(SDL_Event e, int &status);
    void showFigure(SDL_Renderer * renderer,  int &status);
    void showFigureFire(SDL_Renderer * renderer,  int &status, int cnt);

    void setCountFigure(int i);
protected:
    int count_figure;
private:


};