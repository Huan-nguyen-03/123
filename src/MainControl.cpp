#include "MainControl.h"

using namespace std;


MainControl::MainControl()
{

    window = NULL;
    renderer = NULL;
    // end_loop = false;
    // fire = false;
    // checkCol = false;
    
    // status = GO_RIGHT;
    // eventRepeat = 0;
    
    // dx = 0;
    // cnt_figure = 3;
    // cnt_explosion = 0;
    turn = true;
    convertTurn = 0;
}

MainControl::~MainControl() 
{

}

void MainControl::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void MainControl::initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }

    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
    }

     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void MainControl::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void MainControl::close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Window* MainControl::getWindow() const
{
    return window;
}

SDL_Renderer* MainControl::getRenderer()const
{
    return renderer;
}

void MainControl::run()
{
    initSDL(window, renderer);
    player1.loadMedia(renderer);
    player2.loadMedia(renderer);
    map.loadMap(renderer);
    turnImage.loadTurnImage(renderer);
    start.loadStart(renderer);
    end.loadEnd(renderer);
    start.handleEvent(renderer, e, play);
    
    
    sound.loadMedia();
    if (!play)
    {
        close();
        return;
    }
    else
    {
        while(play)
        {
            sound.showMusic(1);
            while(player1.checkDead() == false && player2.checkDead() == false)
            {
                startTime = SDL_GetTicks();
                map.renderTexture(0, renderer, 0, 0);
                while(SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        close();
                        return;
                    }
                    if (turn)
                        player1.handleEvent(e, turn);
                    else
                        player2.handleEvent(e, turn);
                }
                
                if (turn)
                {
                    player1.show(renderer, player2.getPositionExplosion(), player2.minus, true, convertTurn);
                    player2.show(renderer, player1.getPositionExplosion(), player1.minus, false, convertTurn);
                }
                else
                {
                    player2.show(renderer, player1.getPositionExplosion(), player1.minus, true, convertTurn);
                    player1.show(renderer, player2.getPositionExplosion(), player2.minus, false, convertTurn);
                }
                
                if (convertTurn == 1)
                {
                    turn = !turn;
                    convertTurn = 0;
                    turnImage.showTurnImage(0, renderer);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(500);
                }
                else if (convertTurn == 2)
                {
                    turn = !turn;
                    convertTurn = 0;
                    turnImage.showTurnImage(1, renderer);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(500);
                }
                else if (convertTurn == 3)
                {
                    convertTurn = 1;
                }
                else if (convertTurn == 4)
                {
                    convertTurn = 2;
                }
                else
                {
                    SDL_RenderPresent(renderer);

                    endTime = SDL_GetTicks();
                    if (endTime - startTime < 1000/FRAMES_PER_SECOND)
                        SDL_Delay(1000/FRAMES_PER_SECOND - endTime + startTime);
                }
                
            }
            ///////////////////// dead, end game
            if (player1.checkDead())
            {
                sound.haltMusic();
                map.renderTexture(0, renderer, 0, 0);
                player1.showDead(renderer);
                player2.show(renderer, player1.getPositionExplosion(), player1.minus, false, convertTurn);
            }
            else
            {
                sound.haltMusic();
                map.renderTexture(0, renderer, 0, 0);
                player2.showDead(renderer);
                player1.show(renderer, player1.getPositionExplosion(), player1.minus, false, convertTurn);
            }
            
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            
            end.handleEvent(renderer, e, play);
            player1.resetPlayer();
            player2.resetPlayer();
        }
        
    }

    
    
    waitUntilKeyPressed();
    close();

}
