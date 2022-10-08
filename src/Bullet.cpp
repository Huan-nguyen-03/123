#include "Bullet.h"

using namespace std;

Bullet :: Bullet()
{
    angle = 65;
    force = 0;

    holdSpace = false;
}

Bullet :: ~Bullet()
{

}

void Bullet:: loadBullet(SDL_Renderer * renderer)
{
    loadFromFile("images/bullet.png", renderer);
    loadFromFile("images/Fly_bullet.png", renderer);

    sound.loadMedia();
}

void Bullet::handleEvent(SDL_Event e, int & eventRepeat, bool & fire)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym== SDLK_UP)                                 //  editing angle
            angle ++;
        else if (e.key.keysym.sym== SDLK_DOWN)
            angle --;

        
        if (e.key.keysym.sym == SDLK_SPACE)                             //  editing force
        {
            holdSpace = true;
            //cout << "start " << startTime << endl;                
        }
    }

    if (holdSpace)
    {
        eventRepeat++;
        if (eventRepeat==1)
            startTime = SDL_GetTicks();
        force = SDL_GetTicks() - startTime;
        force = min(600*8, force);   
    }

    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
    {
        endTime = SDL_GetTicks();
        eventRepeat = 0;
        force = int(endTime - startTime);   
        force = min(600*8, force);                                // force use to fire
        holdSpace = false;

        fire = true;
        sound.showChunk(0, 0);
    }
    

}

void Bullet::showBullet (SDL_Renderer* renderer, int x, int y, bool & check_fly, int status)
{
    if (check_fly)                                          // show fly bullet
    {
        SDL_Point  p ;
        p.x = x+108/2;
        p.y = y+53/2;
        render(1, x, y, renderer, 0, &p , ((status == GO_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
        
    }
    else if (check_fly == false )                           //  show normal bullet 
        renderTexture(0, renderer, x, y);
}



void Bullet::loadForceBar(SDL_Renderer * renderer)
{
    loadFromFile("images/forcebar.png", renderer);
    loadFromFile("images/Angle.png", renderer);
}


void Bullet::showForceBar(SDL_Renderer * renderer, int x, int y)
{
    renderTexture(2, renderer, x, y);
    
}

void Bullet::loadAngle(SDL_Renderer * renderer)                      // load index of angle to display on screen
{
    
   
   
   
    SDL_Color blue = {0, 0, 255};
    TTF_Font * font = TTF_OpenFont("Fonts/[Easycome]Manga 15.ttf", 36 );
    
    string str = to_string(angle);
    loadFromRenderedText(font, str ,blue, renderer);
    //renderTexture(1, renderer, 525, 50);
    TTF_CloseFont(font);

}

void Bullet::showAngle(SDL_Renderer * renderer, int x, int y)       
{
    renderTexture(4, renderer, x, y);
}

void Bullet::showImageAngle(SDL_Renderer * renderer, int x, int y, bool status)
{
    SDL_Point p = {0, 7};
    
    
    if (status == GO_RIGHT)
        render(3, x+100, y+45, renderer, -angle, &p, SDL_FLIP_NONE);
    else 
        render(3, x+40, y+45, renderer, 180 + angle, &p, SDL_FLIP_NONE);
        
}

void Bullet::loadForce(SDL_Renderer * renderer)                     // load index of force to display on screen
{
    // SDL_Color blue = {0, 0, 255};
    // TTF_Font * font = TTF_OpenFont("Fonts/[Easycome]Manga 15.ttf", 36 );
    
    // string str = to_string(force);
    // loadFromRenderedText(font, str ,blue, renderer);

    loadFromFile("images/rec.png", renderer);
    setBlendMode(5, SDL_BLENDMODE_BLEND);
    setAlpha(5, 90);
}



void Bullet::showForce(SDL_Renderer * renderer, int x, int y)
{
    int w = 1 + force/8;

    render1part(5, renderer, x, y, w , 40);
    SDL_DestroyTexture(texture.at(5));
    SDL_DestroyTexture(texture.at(4));
    texture.pop_back();
    texture.pop_back();
    width.pop_back();
    width.pop_back();
    height.pop_back();
    height.pop_back();
    texture.shrink_to_fit();
    width.shrink_to_fit();
    height.shrink_to_fit();
    // cout << texture.size() << " " << width.size() << " " << height.size();
}


int Bullet::getAngle()
{
    return angle;
}

int Bullet::getForce()
{
    return force;
}