#include "Paddle.h"

//Sets padddle height and width depending on inputs
Paddle::Paddle()
{
    speed = 7;
    AIControlled = false;
}

Paddle::~Paddle()
{
}

void Paddle::setWidth(int newWidth)
{
    hitBox.w = newWidth;
}

void Paddle::setHeight(int newHeight)
{
    hitBox.h = newHeight + 30;
}

void Paddle::setPosX(int newX)
{
    hitBox.x = newX;
}

void Paddle::setPosY(int newY)
{
    hitBox.y = newY;
}

//Moves paddle to new location
void Paddle::move(int screenH,  SDL_Event& e )
{
    hitBox.y = hitBox.y + vY;
    int distanceFromBottom = hitBox.y + hitBox.h;

    if(hitBox.y < 0 || distanceFromBottom >= screenH)
    {
        hitBox.y = hitBox.y - vY;
    }
}

//Moves AI paddle to new location
void Paddle::moveAI(int screenH, int ballPosY)
{
    if (ballPosY < hitBox.y + hitBox.h/2)
    {
        hitBox.y = hitBox.y - speed;
    }
    else if(ballPosY > hitBox.y + hitBox.h/2)
    {
        hitBox.y = hitBox.y + speed;
    }

    //Bounds checking
    if(hitBox.y < 0)
    {
        hitBox.y = 0;
    }
    else if(hitBox.y > screenH - hitBox.h)
    {
        hitBox.y = screenH - hitBox.h;
    }
}

//Processing input for player one movement
void Paddle::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: vY -= speed; break;
            case SDLK_s: vY += speed; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: vY += speed; break;
            case SDLK_s: vY -= speed; break;
        }
    }
}

//Processing input for player two movement
void Paddle::handleEventP2( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vY -= speed; break;
            case SDLK_DOWN: vY += speed; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vY += speed; break;
            case SDLK_DOWN: vY -= speed; break;
        }
    }
}
