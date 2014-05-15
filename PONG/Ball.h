#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

#define PI 3.1415926535897932

using std::string;

#include "Object.h"
#include "Paddle.h"

class Ball: public Object
{
public:
    Ball(int x, int y, int vx, int vy); //constructor
    ~Ball(); //deconstructor
    int move(int screenH,  int screenW, Paddle P1, Paddle P2); //move the ball
                                                                //and collision check
    void setBallTex(string texName);
    void timer();
    void bounce(Paddle P, char UD);
    SDL_Surface* ballSurf;
    SDL_Texture* ballTex;

private:
    int originX, originY, velCap, negVelCap;
    string texName;
};

#endif // PADDLE_H

