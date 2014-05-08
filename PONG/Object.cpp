#include "Object.h"

Object::Object()
{
    //Initialize the position
    posX = 0;
    posY = 0;

	//Set collision box dimension
	hitBox.w = 0;
	hitBox.h = 0;

    //used by functions in derived classes
	velocityX = 0;
	velocityY = 0;
}

/*void Object::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velocityY -= maxVelocity; break;
            case SDLK_DOWN: velocityY += maxVelocity; break;
            case SDLK_LEFT: velocityX -= maxVelocity; break;
            case SDLK_RIGHT: velocityX += maxVelocity; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velocityY += maxVelocity; break;
            case SDLK_DOWN: velocityY -= maxVelocity; break;
            case SDLK_LEFT: velocityX += maxVelocity; break;
            case SDLK_RIGHT: velocityX -= maxVelocity; break;
        }
    }
}*/
