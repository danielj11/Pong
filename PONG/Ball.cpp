#include "Ball.h"

Ball::Ball(int x = 0, int y = 0, int vx = 0, int vy = 0)
{
    hitBox.x = x - 30;
    hitBox.y = y - 20;
    originX = x;
    originY = y;

    hitBox.h = 30;
    hitBox.w = 45;

    vX = vx;
    vY = vy;

    //vertical velocity will never go past 10
    velCap = 10;
    negVelCap = -10;
}

Ball::~Ball()
{
    SDL_FreeSurface(ballSurf);
}

int Ball::move(int screenH, int screenW, Paddle P1, Paddle P2)
{
    //Who has hit the other player's "DeadZone"?
    //1 = playerOne gets a point, 2 = playerTwo gets a point
    int PlayerPlus = 0;

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
            vX = -vX;

            if (hitBox.y < (P1.hitBox.y + P1.hitBox.h / 2)) //it is above, so add some velocity
            {
                bounce(P1, 'u');
            }
            else //it is below, so subtract some velocity
            {
                bounce(P1, 'd');
            }
        }
    }

    //check for the P2 paddles pos
    //is it at or past the P2 paddle?
    else if(hitBox.x >= (P2.hitBox.x - P2.hitBox.w) - 20)
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

            if (hitBox.y < (P2.hitBox.y + P2.hitBox.h / 2)) //it is above, so add some velocity
            {
                bounce(P2, 'u');
            }
            else //it is below, so subtract some velocity
            {
                bounce(P2, 'd');
            }
        }
    }

    /****************************************
    *  Check ball hitting ceiling or floor  *
    ****************************************/

    //has it hit the floor or cieling? if so bounce it
    else if(hitBox.y <= 0 || hitBox.y >= (screenH - hitBox.h))
    {
        vY = -vY;
    }

    return PlayerPlus;
}

void Ball::bounce(Paddle P, char UD)
{
    int adjust = P.hitBox.y + P.hitBox.h / 2;
    int adjustMod = 2*velCap;

    //if it hits the center
    if (hitBox.y == (P.hitBox.y + P.hitBox.h / 2))
    {
        vY = 0;
        return;
    }

    //while it is not at center, adjust to fit
    if (UD == 'u')
    {
        while (adjust > hitBox.y)
        {
            adjust--;
        }
    }
    else
    {
        while (adjust < hitBox.y)
        {
            adjust++;
        }
    }

    adjust = adjust / (velCap + adjustMod); //adjust this to something more reasonable

    if (adjust < 0)
    {
        adjust = 1;
    }

    if (UD == 'u') //upper part of the paddle
    {
        vY -= adjust;

        if (vY < negVelCap)
        {
            vY = negVelCap;
        }
    }
    else //lower part of the paddle
    {
        vY += adjust;

        if (vY > velCap)
        {
            vY = velCap;
        }
    }
}

void Ball::timer()
{
    SDL_Delay(1000); //wait 1 second
}
