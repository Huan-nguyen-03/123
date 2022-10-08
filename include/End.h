#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Texture.h>

using namespace std;

class End : public Texture
{
public:
    End();
    ~End();

    void loadEnd(SDL_Renderer * renderer);
    void showEnd(SDL_Renderer * renderer);

    void handleEvent(SDL_Renderer * renderer,SDL_Event &e, bool &play);
protected:
    int checkChoose;
private:

};