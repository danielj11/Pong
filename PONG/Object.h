#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

class Object
{
    public:
		//Maximum axis velocity of the dot
		int maxVelocity;

		//Initializes the variables
		Object();

		//Starting position
		int posX, posY;

		//Starting velocity, may not need
		int velocityX, velocityY;

		//Object's collision box
		SDL_Rect hitBox;
};

#endif // OBJECT_H
