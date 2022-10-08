#include "Figure.h"

using namespace std;

Figure :: Figure()
{
    x.push_back(100);
    y.push_back(380);
    count_figure = 0;
}

Figure :: ~Figure()
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

void Figure :: loadMedia(SDL_Renderer * renderer)
{
    loadFromFile("images/Figure1.png", renderer);
    loadFromFile("images/Figure2.png", renderer);
    loadFromFile("images/Figure3.png", renderer);
    loadFromFile("images/Figure4.png", renderer);
    loadFromFile("images/Figure5.png", renderer);

}

void Figure :: handleEvent(SDL_Event e, int &status)
{
    // while(SDL_PollEvent(&e) != 0)
    // {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_RIGHT)
            {
                x.at(0) += 5;
                if (x.at(0) > SCREEN_WIDTH - FIGURE_WIDTH ) x.at(0) -= 5;
                status = GO_RIGHT;
                count_figure = (count_figure+1)%3;
                //cout << count_figure << " ";
            }
            else if (e.key.keysym.sym == SDLK_LEFT)
            {
                x.at(0) -= 5;
                if (x.at(0) <0 ) x.at(0) += 5;
                status = GO_LEFT;
                count_figure = (count_figure+1)%3;
                //cout << count_figure << " ";
            }
        }
        
        if (e.type == SDL_KEYUP)
            count_figure = 0;
    // }
}

void Figure::showFigure(SDL_Renderer * renderer, int &status)
{
    SDL_Point point;
    point.x = x.at(0);
    point.y = y.at(0);
    //renderTexture(count_figure, renderer, x.at(0), y.at(0));
    render(count_figure, x.at(0), y.at(0), renderer, 0, &point , ((status == GO_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}

void Figure::showFigureFire(SDL_Renderer * renderer,  int &status, int cnt)
{
    count_figure = cnt;
    SDL_Point point;
    point.x = x.at(0);
    point.y = y.at(0);
    //renderTexture(count_figure, renderer, x.at(0), y.at(0));
    render(count_figure, x.at(0), y.at(0), renderer, 0, &point , ((status == GO_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));  
}

void Figure::setCountFigure(int i)
{
    count_figure = i;
}