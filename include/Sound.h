#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"


using namespace std;

class Sound
{
public:
    Sound();
    ~Sound();
    void loadMedia();

    void loadMusic(char* path);
    void loadChunk(char* path);

    void showMusic(int i);
    void showChunk(int i, int loop);

    void pauseMusic(int i);
    void haltMusic();

    
protected:
    vector <Mix_Music*> music;
    vector <Mix_Chunk*> chunk;

private:

};