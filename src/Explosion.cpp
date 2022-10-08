#include "Explosion.h"

using namespace std;

Explosion :: Explosion()
{
    count_explosion = 0;
    x_exp = 0;
    y_exp = 0;
}

Explosion :: ~Explosion()
{
    x.clear();
    y.clear();
    width.clear();
    height.clear();
    texture.clear();

    x.shrink_to_fit();
    y.shrink_to_fit();
    width.shrink_to_fit();
    height.shrink_to_fit();
    texture.shrink_to_fit();
}

void Explosion :: loadExplosion(SDL_Renderer * renderer)
{
    loadFromFile("images/explosion1.png", renderer);
    loadFromFile("images/explosion2.png", renderer);
    loadFromFile("images/explosion3.png", renderer);
    loadFromFile("images/explosion4.png", renderer);
    loadFromFile("images/explosion5.png", renderer);

}

void Explosion :: show(SDL_Renderer * renderer , int i)
{
        renderTexture(i, renderer, x_exp, y_exp);

}

void Explosion:: setX(int i)
{
    x_exp = i;
}

void Explosion:: setY(int i)
{
    y_exp = i;
}