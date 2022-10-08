#include "TurnImage.h"

using namespace std;

TurnImage::TurnImage()
{

}

TurnImage::~TurnImage()
{

}

void TurnImage::loadTurnImage(SDL_Renderer * renderer)
{
    loadFromFile("images/player1.png", renderer);
    loadFromFile("images/player2.png", renderer);
}

void TurnImage:: showTurnImage(int i, SDL_Renderer * renderer)
{
    renderTexture(i, renderer, 400, 200);
}