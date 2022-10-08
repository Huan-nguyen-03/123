#include "Player1.h"

using namespace std;

Player1::Player1()
{
    fire = false;
    checkCol = false;
    
    status = GO_RIGHT;
    eventRepeat = 0;
    
    dx = 0;
    t = 0;
    
    cnt_figure = 3;
    cnt_explosion = 0;
    
    minus = false;
    check_fly = false;
}

Player1::~Player1()
{

}


//////////////////////////////////////////////////

void Player1::loadMedia(SDL_Renderer * renderer)
{
    //map.loadMap(renderer);
    figure.loadMedia(renderer);
    bullet.loadBullet(renderer);
    explosion.loadExplosion(renderer);
    fly.loadFly(renderer);
    sound.loadMedia();
    bullet.loadForceBar(renderer);
    turnImage.loadTurnImage(renderer);
}

void Player1::handleEvent(SDL_Event &e, bool & turn)
{
    fly.handleEvent(e, check_fly, 15, 520);
    figure.handleEvent(e, status);           
    bullet.handleEvent(e, eventRepeat, fire);
    // if (fire)   
    // {
    //     turn = !turn;
        
    // }
}

void Player1::show(SDL_Renderer * renderer, int explosion_pos, bool &otherMinus, bool turn,int &convertTurn)
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
    bullet.showForceBar(renderer, 300, 505);
    bullet.showAngle(renderer, 100, 510);
    bullet.showForce(renderer, 300, 505);
    figure.showHP(renderer, 100, 540);
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

    fly.showFly(15, 520, renderer, check_fly);
}










void Player1::showTrajectory(SDL_Renderer * renderer, int angle, int force, int & dx, int x, int y, int &status, int &convertTurn)
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
        x_start = x - 50;
        y_start = y + 20;
    }
    
    int x_pos = x_start;
    int y_pos = y_start;
    //
    
    
    
    if (status == GO_RIGHT)
        x_pos = x_start + initialVelocity * cos(rad_angle) * t;
    if (status == GO_LEFT)
        x_pos = x_start - initialVelocity * cos(rad_angle) * t;
    
    y_pos = y_start - initialVelocity * sin(rad_angle) * t + 0.5 * GRAVITY * t*t;

    bullet.showBullet(renderer, x_pos, y_pos, check_fly, status);
    t += 0.23;
 
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
            convertTurn = 4;
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

void Player1::showAllExplosion(SDL_Renderer * renderer, int &convertTurn)
{
    // turnImage.showTurnImage(1, renderer);
    explosion.show(renderer, cnt_explosion);
    cnt_explosion ++;
    SDL_Delay(30);
    if (cnt_explosion == 4)
    {
        checkCol = false;        
        convertTurn = 4;
    }
}


int Player1::getPositionExplosion()
{
    return explosion.getX();
}

bool Player1::getMinus()
{
    return minus;
}

bool Player1:: checkDead()
{
    if (figure.getHP() <=0 )    
        return true;
    return false;
}

void Player1:: showDead(SDL_Renderer * renderer)
{
    sound.showChunk(2, 0);
    figure.showDead_F(renderer, figure.getX(0), figure.getY(0));
}

void Player1:: resetPlayer()
{
    figure.reset(1000, 100);
}