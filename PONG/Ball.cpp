#include "Ball.h"

Ball::Ball(int x = 0, int y = 0, int vx = 0, int vy = 0)
{
    hitBox.x = x - 30;
    hitBox.y = y - 20;
    originX = x;
    originY = y;

    hitBox.h = 20;
    hitBox.w = 30;

    vX = vx;
    vY = vy;

    velCap = (vx + vy) / 2;
}

Ball::~Ball()
{
    SDL_FreeSurface(ballTex);
}

int Ball::move(int screenH, int screenW, Paddle P1, Paddle P2)
{
    //Who has hit the other player's "DeadZone"?
    //1 = playerOne gets a point, 2 = playerTwo gets a point
    int PlayerPlus = 0;
    int adjust = 0;

    /*************
    *  Movement  *
    *************/

    hitBox.y += vY;
    hitBox.x += vX;

    /****************************
    *  Check for Paddle Misses  *
    *  and return winner's #    *
    ****************************/

    //check for the P1 paddles pos
    //is it at or past the P1 paddle?
    if(hitBox.x <= (P1.hitBox.x + P1.hitBox.w) - 10)
    {
        //is it above or below the paddle
        if (hitBox.y <= P1.hitBox.y - hitBox.h || hitBox.y >= (P1.hitBox.y + P1.hitBox.h))
        {
            PlayerPlus = 2; //player 2 gets the point
            hitBox.x = originX;
            hitBox.y = originY;
        }
        else //bounce off of P1
        {
            vX = 45 - vX;
        }
    }

    //check for the P2 paddles pos
    //is it at or past the P2 paddle?
    else if(hitBox.x >= (P2.hitBox.x - P2.hitBox.w) + 10)
    {
        //is it above or below the paddle
        if (hitBox.y <= P2.hitBox.y - hitBox.h || hitBox.y >= (P2.hitBox.y + P2.hitBox.h))
        {
            PlayerPlus = 1; //player 2 gets the point
            hitBox.x = originX;
            hitBox.y = originY;
        }
        else //bounce off of P2
        {
            vX = -vX;
        }
    }

    /****************************************
    *  Check ball hitting cieling or floor  *
    ****************************************/

    //has it hit the floor or cieling? if so bounce it
    else if(hitBox.y <= 0 || hitBox.y >= (screenH - hitBox.h))
    {
        vY = -vY;
    }

    return PlayerPlus;
}

void Ball::timer()
{
    //now put the tex for number 3
    //SDL_Delay(1000); //wait 1 second
    //now put the tex for number 2
    //SDL_Delay(1000); //wait 1 second
    //now put the tex for number 1
    //SDL_Delay(1000); //wait 1 second
    //reapply ball texture
}
