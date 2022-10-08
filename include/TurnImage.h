#pragma once

#include <iostream>
#include "Texture.h"
#include "Constant.h"


using namespace std;

class TurnImage : public Texture
{
public:
    TurnImage();
    ~TurnImage();
    void loadTurnImage(SDL_Renderer * renderer);
    void showTurnImage(int i, SDL_Renderer * renderer);

protected:
private:

};
