#include "Paddle.h"

//Sets padddle height and width depending on inputs
Paddle::Paddle(int paddleW, int paddleH)
{
    hitBox.w = paddleW;
    hitBox.h = paddleH;
    speed = 7;

    ///Will add back later
    /*if (computerPlayer)
    {
        playerControlled = false;
    }
    else
    {
        playerControlled = true;
    }*/


}

void Paddle::move(int screenH,  SDL_Event& e )
{
    hitBox.y = hitBox.y + velocityY;
    int distanceFromBottom = hitBox.y + hitBox.h;

    if(hitBox.y < 0 || distanceFromBottom >= screenH)
    {
        hitBox.y = hitBox.y - velocityY;
    }
}

void Paddle::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velocityY -= speed; break;
            case SDLK_DOWN: velocityY += speed; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velocityY += speed; break;
            case SDLK_DOWN: velocityY -= speed; break;
        }
    }
}
