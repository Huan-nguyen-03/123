#include "Bullet.h"

using namespace std;

Bullet :: Bullet()
{
    angle = 65;
}

Bullet :: ~Bullet()
{

}

void Bullet:: loadBullet(SDL_Renderer * renderer)
{
    loadFromFile("images/bullet.png", renderer);
}

void Bullet::handleEvent(SDL_Event e, int & eventRepeat, bool & fire)
{
    // while(SDL_PollEvent(&e) != 0)
    // {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym== SDLK_UP)
                angle ++;
            else if (e.key.keysym.sym== SDLK_DOWN)
                angle --;


            if (e.key.keysym.sym == SDLK_SPACE) {
                eventRepeat++;
                if (eventRepeat==1)
                    startTime = SDL_GetTicks();
                
                //cout << "start " << startTime << endl;                
            }
        }

        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
        {
            endTime = SDL_GetTicks();
            // cout << "end "<< endTime << endl;
            eventRepeat = 0;
            force = int(endTime - startTime);
            cout << "force " <<  force << endl;
            fire = true;
        }
    // }

}

// void Bullet :: showBullet (SDL_Renderer* renderer, int x, int y, int status)
// {
//     double rad_angle = angle*1.0/180*M_PI;
//     // first position
//     int initialVelocity = force / 10;
//     int x_start;
//     int y_start;
//     if (status == GO_RIGHT)
//     {
//         x_start = x + 50;
//         y_start = y + 20;
//     }
//     else if (status == GO_LEFT)
//     {
//         x_start = x - 50;
//         y_start = y + 20;
//     }
    
//     int x_pos = x_start;
//     int y_pos = y_start;
//     //
//     int dx = 0;
//     while (!checkCollision(y_pos))
//     {
//         x_pos = x_start + dx;
//         y_pos = y_start - dx* tan(rad_angle) + 0.5 * GRAVITY * (dx / (initialVelocity * cos(rad_angle))) * (dx / (initialVelocity * cos(rad_angle)));
        
//         renderTexture(0, renderer, x_pos, y_pos);
//         SDL_RenderPresent(renderer);
//         dx +=10;
//         cout << x_pos << " " << y_pos << endl;
//         SDL_Delay(10);
//     }
    

// }


void Bullet::showBullet (SDL_Renderer* renderer, int x, int y)
{
    renderTexture(0, renderer, x, y);
}


int Bullet::getAngle()
{
    return angle;
}

int Bullet::getForce()
{
    return force;
}