#include "Player2.h"

using namespace std;

Player2::Player2()
{
    fire = false;
    checkCol = false;
    
    status = GO_LEFT;
    eventRepeat = 0;
    
    dx = 0;
    t = 0;
    cnt_figure = 3;
    cnt_explosion = 0;
    
    minus = false;
    check_fly = false;

    figure = Figure(1000);
}

Player2::~Player2()
{

}


//////////////////////////////////////////////////

void Player2::loadMedia(SDL_Renderer * renderer)
{
    //map.loadMap(renderer);
    figure.loadMedia(renderer);
    bullet.loadBullet(renderer);
    explosion.loadExplosion(renderer);
    fly.loadFly(renderer);
    sound.loadMedia();
    bullet.loadForceBar(renderer);
}

void Player2::handleEvent(SDL_Event &e, bool & turn)
{
    fly.handleEvent(e, check_fly, 1100, 520);
    figure.handleEvent(e, status);           
    bullet.handleEvent(e, eventRepeat, fire);
    // if (fire)   
    // {
    //     turn = !turn;
        
    // }
}

void Player2::show(SDL_Renderer * renderer, int explosion_pos, bool &otherMinus, bool turn, int &convertTurn)
{

    figure.showFigure(renderer, status);
    if (fire)
    {
        figure.showFigureFire(renderer, status, cnt_figure);
        showTrajectory(renderer, bullet.getAngle(), bullet.getForce(), dx, figure.getX(0), figure.getY(0), status, convertTurn);
        cnt_figure = min((cnt_figure + 1), 4);
        
    }

    if (checkCol)
    {
        showAllExplosion(renderer, convertTurn);
        minus = true;
    }
    bullet.loadAngle(renderer);
    bullet.loadForce(renderer);
    figure.loadHP(renderer);
    bullet.showForceBar(renderer, 300, 555);
    bullet.showAngle(renderer, 900, 510);
    bullet.showForce(renderer, 300, 555);
    figure.showHP(renderer, 900, 540);
    if (turn)
        bullet.showImageAngle(renderer, figure.getX(0), figure.getY(0), status);

    if (otherMinus)
    {
        if (figure.checkHit(explosion_pos, status))
        {
            figure.minusHP(explosion_pos, status);
            figure.loadMinusHP(renderer);
            figure.showMinusHP(renderer, figure.getX(0), figure.getY(0)-100);
        }
        otherMinus = false;
    }

    fly.showFly(1100, 520, renderer, check_fly);
}










void Player2::showTrajectory(SDL_Renderer * renderer, int angle, int force, int & dx, int x, int y, int &status, int &convertTurn)
{
    double rad_angle = angle*1.0/180*M_PI;
    // first position
    int initialVelocity = force / 25;
    int x_start;
    int y_start;
    if (status == GO_RIGHT)
    {
        x_start = x + 50;
        y_start = y + 20;
    }
    else if (status == GO_LEFT)
    {
        x_start = x ;
        y_start = y + 20;
    }
    
    int x_pos = x_start;
    int y_pos = y_start;
    //
    
    
    // x_pos = x_start + dx;
    // y_pos = y_start - abs(dx)* tan(rad_angle) + 0.5 * GRAVITY * (dx / (initialVelocity * cos(rad_angle))) * (dx / (initialVelocity * cos(rad_angle)));
    if (status == GO_RIGHT)
        x_pos = x_start + initialVelocity * cos(rad_angle) * t;
    if (status == GO_LEFT)
        x_pos = x_start - initialVelocity * cos(rad_angle) * t;
    
    y_pos = y_start - initialVelocity * sin(rad_angle) * t + 0.5 * GRAVITY * t*t;

    bullet.showBullet(renderer, x_pos, y_pos, check_fly, status);
    t += 0.23;
    //cout << x_pos << " " << y_pos << endl;

    if (checkCollision(y_pos))
    {
        
        explosion.setX(x_pos - 125);
        explosion.setY(y_pos - 100);
        fire = false;
        if (!check_fly)
        {
            checkCol = true;
            sound.showChunk(1, 0);
        }
        else 
        {
            convertTurn = 3;
            if (x_pos < 1200 && x_pos > 0)
                figure.setX(0, x_pos);
        }
        dx = 0;
        t = 0;
        cnt_figure = 3;
        cnt_explosion = 0;
        figure.setCountFigure(0);
        check_fly = false;
    }
   // SDL_Delay(10);
}

void Player2::showAllExplosion(SDL_Renderer * renderer, int &convertTurn)
{
    explosion.show(renderer, cnt_explosion);
    SDL_Delay(15);
    cnt_explosion ++;
    if (cnt_explosion == 4)
    {
        checkCol = false;
        convertTurn = 3;
    }
}


int Player2::getPositionExplosion()
{
    return explosion.getX();
}

bool Player2::getMinus()
{
    return minus;
}


bool Player2:: checkDead()
{
    if (figure.getHP() <=0 )    
        return true;
    return false;
}

void Player2:: showDead(SDL_Renderer * renderer)
{
    sound.showChunk(2, 0);
    figure.showDead_F(renderer, figure.getX(0), figure.getY(0));
}

void Player2:: resetPlayer()
{
    figure.reset(1000, 1000);
    status = GO_LEFT;
}