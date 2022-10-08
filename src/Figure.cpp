#include "Figure.h"

using namespace std;


Figure :: Figure(int x_begin)
{
    x.push_back(x_begin);
    y.push_back(380); //380
    count_figure = 0;
    hp = 1000;
    dame = 0;
    
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

void Figure :: loadMedia(SDL_Renderer * renderer)           // animation of figure
{
    loadFromFile("images/Figure1.png", renderer);
    loadFromFile("images/Figure2.png", renderer);
    loadFromFile("images/Figure3.png", renderer);
    loadFromFile("images/Figure4.png", renderer);
    loadFromFile("images/Figure5.png", renderer);
    loadFromFile("images/Figure6.png", renderer);

    sound.loadMedia();
}

void Figure :: handleEvent(SDL_Event e, int &status)        // handle move
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_RIGHT)
        {
            x.at(0) += 5;
            if (x.at(0) > SCREEN_WIDTH - FIGURE_WIDTH ) x.at(0) -= 5;
            status = GO_RIGHT;
            count_figure = (count_figure+1)%3;
            sound.showChunk(3,0);
        }
        else if (e.key.keysym.sym == SDLK_LEFT)
        {
            x.at(0) -= 5;
            if (x.at(0) <0 ) x.at(0) += 5;
            status = GO_LEFT;
            count_figure = (count_figure+1)%3;
            sound.showChunk(3, 0);
        }
    }
    
    if (e.type == SDL_KEYUP)
        count_figure = 0;

}

void Figure::showFigure(SDL_Renderer * renderer, int &status)
{
    SDL_Point point;
    point.x = x.at(0);
    point.y = y.at(0);
    //renderTexture(count_figure, renderer, x.at(0), y.at(0));
    render(count_figure, x.at(0), y.at(0), renderer, 0, &point , ((status == GO_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}

void Figure::showFigureFire(SDL_Renderer * renderer,  int &status, int cnt)     // show shooting posture of figure
{
    count_figure = cnt;
    SDL_Point point;
    point.x = x.at(0);
    point.y = y.at(0);
    //renderTexture(count_figure, renderer, x.at(0), y.at(0));
    render(count_figure, x.at(0), y.at(0), renderer, 0, &point , ((status == GO_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));  
}

void Figure::loadHP(SDL_Renderer * renderer)                    // load index of health point (HP)
{
    SDL_Color blue = {0, 0, 255};
    TTF_Font * font = TTF_OpenFont("Fonts/[Easycome]Manga 15.ttf", 36 );
    
    string str = "HP: " + to_string(hp);
    loadFromRenderedText(font, str ,blue, renderer);
    TTF_CloseFont(font);
  
}
void Figure::showHP(SDL_Renderer * renderer, int x, int y)      // display index of health point (HP)
{

    renderTexture(6, renderer, x, y);
    SDL_DestroyTexture(texture.at(6));
    texture.pop_back();
    texture.shrink_to_fit();
    width.pop_back();
    width.shrink_to_fit();
    height.pop_back();
    height.shrink_to_fit();
    
    
}


bool Figure::checkHit(int explosion_pos, int status)        //check if the character is hit or not
{
    cout << "ex " << explosion_pos << "   " << "pos " << x.at(0)  << endl;
    if (status == GO_RIGHT)
    {
        if (explosion_pos + 150   < (x.at(0) + 60 + 60) && explosion_pos + 150 > (x.at(0) + 60 - 60))
        {
        
            return true;
        }
    }
    else
    {
          if (explosion_pos +150  < (x.at(0) + 80 + 60) && explosion_pos + 150> (x.at(0) + 80 - 60))
        {
        
            return true;
        }
    }

    return false;
 
}
void Figure::minusHP(int explosion_pos, int status)         
{
    if (status == GO_RIGHT)
        dame = (100 - abs((explosion_pos + 150) - (x.at(0)+60)));
    else
        dame = (100 - abs((explosion_pos + 150) - (x.at(0)+80)));
    hp = hp - dame;    

}

int Figure::getHP()
{
    return hp;
}

void Figure::setCountFigure(int i)
{
    count_figure = i;
}

void Figure::showDead_F(SDL_Renderer * renderer, int x, int y)          // show picture when figure dead
{
    renderTexture(5, renderer, x, y);
}

void Figure:: reset(int hp, int pos)
{
    this -> hp = hp;
    x.at(0) = pos;
}

void Figure::loadMinusHP(SDL_Renderer * renderer)
{
    SDL_Color color = {233, 255, 100};
    TTF_Font * font = TTF_OpenFont("Fonts/1Viet-ToCongNgon-Nabila.ttf", 72 );
    int n = dame * 4;
    string str = to_string(n);
    loadFromRenderedText(font, str ,color, renderer);
}

void Figure::showMinusHP(SDL_Renderer * renderer, int x, int y)
{
    renderTexture(6, renderer, x, y);
    texture.pop_back();
}