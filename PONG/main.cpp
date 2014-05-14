#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Controller.h"

using namespace std;

int main( int argc, char* args[] )
{
    srand(time(NULL));

    Controller Nyan;
    Nyan.runGame();

    return 0;
}
