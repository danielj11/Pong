#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <cassert>
#include "Paddle.h"
#include "Ball.h"
#include "SDL_ttf.h"
#include "Score.h"

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Controller
{
public:
    Controller();
    ~Controller();
    bool initialize();
    void runGame();
    void closeGame();
    void processInput(SDL_Event& e);
    void setPaddles(bool isAI);
    void colorChange(int& change, int& choice);
private:
    bool paddleOpp, quit;
    int scoreP1, scoreP2;
    Paddle playerOne;
    Paddle playerTwo;
    Score scoreDisplayP1;
    Score scoreDisplayP2;
    Mix_Music* NyanTheSong; //Song loader
    SDL_Window* gWindow; //Window that will show game
    SDL_Renderer* renderer; //Renderer for the game
    SDL_Surface* winSurface;
    SDL_Texture* winTexture;
    SDL_Surface* dash;
    SDL_Texture* dashTex;
    SDL_Rect dashRect;
};

#endif // CONTROLLER_H
