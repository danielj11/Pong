#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Object.h"

class Paddle: public Object
{
public:
    Paddle();
    ~Paddle();
    void move(int screenH,  SDL_Event& e );
    void moveAI(int screenH, int ballPosY);
    void handleEvent( SDL_Event& e );
    void handleEventP2( SDL_Event& e );
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setPosX(int newX);
    void setPosY(int newY);

    int speed;
    bool AIControlled;
};

#endif // PADDLE_H
