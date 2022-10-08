#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Texture.h>
#include "Sound.h"

using namespace std;

class Start : public Texture
{
public:
    Start();
    ~Start();

    void loadStart(SDL_Renderer * renderer);
    void showStart(SDL_Renderer * renderer);

    void handleEvent(SDL_Renderer * renderer,SDL_Event &e, bool &play);
protected:
    int checkChoose;
    Sound sound;
private:

};