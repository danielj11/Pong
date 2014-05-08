#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "Paddle.h"
#include "Texture.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


class Controller
{
public:
    Controller();
    void runGame();
    bool initialize();
    bool loadMedia();
    void closeGame();
    void renderObject(Object &r);
    void renderBall();
private:
    //Paddle playerOne();
    Texture ballTexture;//Texture for ball
    Texture paddleTexture;//Texture for paddle
    SDL_Window* gWindow; //Window that will show game
    SDL_Renderer* renderer; //Renderer for the game
};

#endif // CONTROLLER_H
