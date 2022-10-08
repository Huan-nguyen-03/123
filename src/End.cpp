#include "End.h"

using namespace std;

End:: End()
{
    checkChoose = 0;              // no choose
}

End:: ~End()
{

}

void End:: loadEnd(SDL_Renderer * renderer)
{
    loadFromFile("images/End.png", renderer);                       // load options play again and exit
    SDL_Color color1 = {200, 0, 0};
    TTF_Font * font1 = TTF_OpenFont("Fonts/0032-LNTH-BarbershopInThailand.ttf", 72 );
    string again = "Play Again";
    string exit = "Exit";
    loadFromRenderedText(font1, again ,color1, renderer);
    loadFromRenderedText(font1, exit ,color1, renderer);

    SDL_Color color2 = {0, 230, 255};                                 // other color 
    TTF_Font * font2 = TTF_OpenFont("Fonts/0032-LNTH-BarbershopInThailand.ttf", 72 );
    loadFromRenderedText(font1, again ,color2, renderer);
    loadFromRenderedText(font1, exit ,color2, renderer);
}

void End::handleEvent(SDL_Renderer * renderer, SDL_Event &e, bool &play)
{
    while (true)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                play = false;
                return;
            }
            if (e.type == SDL_MOUSEMOTION)                                
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
            
                if (x >= 250 && x <= 550 && y >= 350 && y< 450)
                    checkChoose = 1;
                else if (x >= 250 && x <= 450 && y >= 450 && y<= 550)
                    checkChoose = 2;
                else 
                    checkChoose = 0;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;
                if (x >= 250 && x <= 400 && y >= 350 && y<= 400)
                {
                    play = true;
                    return;
                }
                else if (x >= 250 && x <= 400 && y >= 450 && y<= 500)
                {
                    play = false;
                    return;
                }
            }
        }
        
        showEnd(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}

void End::showEnd(SDL_Renderer * renderer)
{
    renderTexture(0, renderer, 0, 0);
    if (checkChoose == 0)
    {
        renderTexture(1, renderer, 250, 350);
        renderTexture(2, renderer, 250, 450);
    }
    else if (checkChoose == 1)
    {
        renderTexture(3, renderer, 250, 350);
        renderTexture(2, renderer, 250, 450);
    }
    else if (checkChoose == 2)
    {
        renderTexture(1, renderer, 250, 350);
        renderTexture(4, renderer, 250, 450);
    }
}
