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
        //Initializes the variables
		Object();
		~Object();

		//Maximum axis velocity of the dot
		int maxVelocity;

		//Postion of the object
		int posX, posY;

		//Velocity for each direction
		int velocityX, velocityY;

		//Object's collision box
		SDL_Rect hitBox;
};

#endif // OBJECT_H
