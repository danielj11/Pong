#include "Object.h"

Object::Object()
{
	//Set rectangle's default position and size
	hitBox.w = 0;
	hitBox.h = 0;
	hitBox.x = 0;
	hitBox.y = 0;

    //used by functions in derived classes
	vX = 0;
	vY = 0;
}

Object::~Object()
{
}
