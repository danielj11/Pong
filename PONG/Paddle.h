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
    Paddle(int paddleW, int paddleH);
    void move(int screenH,  SDL_Event& e );
    void handleEvent( SDL_Event& e );
    int width;
    int height;
    int speed;
    bool playerControlled;
};

#endif // PADDLE_H
