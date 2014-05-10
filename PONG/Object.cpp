#include "Object.h"

Object::Object()
{
    //Initialize position variables
    posX = 0;
    posY = 0;

	//Set rectangle's default position and size
	hitBox.w = 0;
	hitBox.h = 0;
	hitBox.x = 0;
	hitBox.y = 0;

    //used by functions in derived classes
	velocityX = 0;
	velocityY = 0;
}

Object::~Object()
{
}
