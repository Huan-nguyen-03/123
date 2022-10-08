#include "Sound.h"

using namespace std;

Sound::Sound()
{

}

Sound::~Sound()
{
    for (int i=0; i<music.size() ; i++)
        Mix_FreeMusic(music.at(i));
    for (int i=0; i<chunk.size() ; i++)
        Mix_FreeChunk(chunk.at(i));

    music.clear();
    chunk.clear();
    music.shrink_to_fit();
    chunk.shrink_to_fit();
}

void Sound::loadMusic(char* path)
{
    Mix_Music * m = NULL;
    m = Mix_LoadMUS(path);
    if (m == NULL)
        cout << "ko load dc music";
    else
        music.push_back(m);
}

void Sound::loadChunk(char* path)
{
    Mix_Chunk * c = NULL;
    c = Mix_LoadWAV(path);
    if (c == NULL)
        cout << "ko load dc chunk";
    else
        chunk.push_back(c);
}

void Sound::showMusic(int i)
{
    Mix_PlayMusic(music.at(i), -1);
}

void Sound::showChunk(int i, int loop)
{
    Mix_PlayChannel(-1, chunk.at(i), loop);
}

void Sound::loadMedia()
{
    loadMusic("sound/nhacnen.wav");
    loadMusic("sound/nen.wav");
    loadChunk("sound/ban.wav");
    loadChunk("sound/no.wav");
    loadChunk("sound/chet.wav");
    loadChunk("sound/bo.wav");
}

void Sound::pauseMusic(int i)
{
    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

void Sound::haltMusic()
{
    Mix_HaltMusic();
}