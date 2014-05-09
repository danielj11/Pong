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
