#include "Score.h"

Score::Score()
{
    scoreSurface = NULL;
    scoreTexture = NULL;
}

void Score::setImage(int score, SDL_Renderer* renderer)
{
    if(score == 0)
    {
        scoreSurface = SDL_LoadBMP("images/score0.bmp");
    }
    if(score == 1)
    {
        scoreSurface = SDL_LoadBMP("images/score1.bmp");
    }
    if(score == 2)
    {
        scoreSurface = SDL_LoadBMP("images/score2.bmp");
    }
    if(score == 3)
    {
        scoreSurface = SDL_LoadBMP("images/score3.bmp");
    }
    if(score == 4)
    {
        scoreSurface = SDL_LoadBMP("images/score4.bmp");
    }
    if(score == 5)
    {
        scoreSurface = SDL_LoadBMP("images/score5.bmp");
    }
    /*switch (score)
    {
    case 0:
        {
            scoreSurface = SDL_LoadBMP("images/score0.bmp");
        }
    case 1:
        {
            scoreSurface = SDL_LoadBMP("images/score1.bmp");
        }
    case 2:
        {
            scoreSurface = SDL_LoadBMP("images/score2.bmp");
        }
    case 3:
        {
            scoreSurface = SDL_LoadBMP("images/score3.bmp");
        }
    case 4:
        {
            scoreSurface = SDL_LoadBMP("images/score4.bmp");
        }
    case 5:
        {
            scoreSurface = SDL_LoadBMP("images/score5.bmp");
            std::cout << score << std::endl;
        }
    default:
        break;
    }*/

    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
}

void Score::setRect(int playerNum)
{
    if (playerNum == 1)
    {
        displayArea.y = 0;
        displayArea.x = 328;
        displayArea.h = 52;
        displayArea.w = 43;
    }
    else
    {
        displayArea.y = 0;
        displayArea.x = 418;
        displayArea.h = 52;
        displayArea.w = 43;
    }
}

void Score::displayScore(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, scoreTexture, NULL, &displayArea);
}
