#include "Paddle.h"

//Sets padddle height and width depending on intputs
Paddle::Paddle(int paddleW, int paddleH)
{
    width = paddleW;
    height = paddleH;

    //Will add back later
    /*if (computerPlayer)
    {
        playerControlled = false;
    }
    else
    {
        playerControlled = true;
    }*/
}

void Paddle::move(int screenH)
{
    //Move the paddle up or down
    posY += velocityY;
	hitBox.y = posY;

    //If the paddle went too far up or down
    if(( posY < 0 ) || ( posY + height > screenH))
    {
        //Move back
        posY -= velocityY;
		hitBox.y = posY;
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
            case SDLK_UP: velocityY -= speed; std::cout << "UP" << std::endl; break;
            case SDLK_DOWN: velocityY += speed; std::cout << "DOWN" << std::endl; break;
            case SDLK_LEFT: velocityX -= speed; break;
            case SDLK_RIGHT: velocityX += speed; break;
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
            case SDLK_LEFT: velocityX += speed; break;
            case SDLK_RIGHT: velocityX -= speed; break;
        }
    }
}
