#include "MainControl.h"

using namespace std;


MainControl::MainControl()
{

    window = NULL;
    renderer = NULL;
    end_loop = false;
    fire = false;
    checkCol = false;
    
    status = GO_RIGHT;
    eventRepeat = 0;
    
    dx = 0;
    cnt_figure = 3;
    cnt_explosion = 0;
    
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
    map.loadMap(renderer);
    figure.loadMedia(renderer);
    explosion.loadExplosion(renderer);
        
    while (true)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                close();
            figure.handleEvent(e, status);           
            bullet.handleEvent(e, eventRepeat, fire);
            
        }
        map.renderTexture(0, renderer, 0, 0);
        figure.showFigure(renderer, status);
        bullet.loadBullet(renderer);
        if (fire)
        {
            figure.showFigureFire(renderer, status, cnt_figure);
            showTrajectory(bullet.getAngle(), bullet.getForce(), dx, figure.getX(0), figure.getY(0), status);
            cnt_figure = min((cnt_figure + 1), 4);
        }

        if (checkCol)
        {
            showAllExplosion();
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(15);

    }
    
    
    waitUntilKeyPressed();
    close();

}


void MainControl::showTrajectory(int angle, int force, int & dx, int x, int y, int &status)
{
    double rad_angle = angle*1.0/180*M_PI;
    // first position
    int initialVelocity = force / 10;
    int x_start;
    int y_start;
    if (status == GO_RIGHT)
    {
        x_start = x + 50;
        y_start = y + 20;
    }
    else if (status == GO_LEFT)
    {
        x_start = x - 50;
        y_start = y + 20;
    }
    
    int x_pos = x_start;
    int y_pos = y_start;
    //
    
    
    x_pos = x_start + dx;
    y_pos = y_start - abs(dx)* tan(rad_angle) + 0.5 * GRAVITY * (dx / (initialVelocity * cos(rad_angle))) * (dx / (initialVelocity * cos(rad_angle)));
    
    bullet.showBullet(renderer, x_pos, y_pos);
    
    if (status == GO_RIGHT)
        dx +=10;
    if (status == GO_LEFT)
        dx -= 10;
    cout << x_pos << " " << y_pos << endl;

    if (checkCollision(y_pos))
    {
        explosion.setX(x_pos);
        explosion.setY(y_pos - 100);
        fire = false;
        checkCol = true;
        dx = 0;
        cnt_figure = 3;
        cnt_explosion = 0;
        figure.setCountFigure(0);
    }
   // SDL_Delay(10);
}

void MainControl::showAllExplosion()
{
    explosion.show(renderer, cnt_explosion);
    cnt_explosion ++;
    if (cnt_explosion == 4)
        checkCol = false;
}