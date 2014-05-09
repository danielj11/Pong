#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include <iostream>
#include <cassert>
#include "Paddle.h"

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


class Controller
{
public:
    Controller();
    void runGame();
    bool initialize();
    void closeGame();
private:
    SDL_Window* gWindow; //Window that will show game
    SDL_Renderer* renderer; //Renderer for the game
};

#endif // CONTROLLER_H
