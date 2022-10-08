#pragma once

#include <iostream>
#include "Texture.h"
#include "Constant.h"


using namespace std;

class Map : public Texture
{
public:
    Map();
    ~Map();
    void loadMap(SDL_Renderer * renderer);


protected:
private:

};
