#include "Score.h"

Score::Score()
{
    scoreSurface = NULL;
    scoreTexture = NULL;
}

void Score::setImage(int score, SDL_Renderer* renderer)
{
    switch (score)
    {
    case 0:
        {
            scoreSurface = SDL_LoadBMP("images/score0.bmp");
        }
        break;
    case 1:
        {
            scoreSurface = SDL_LoadBMP("images/score1.bmp");
        }
        break;
    case 2:
        {
            scoreSurface = SDL_LoadBMP("images/score2.bmp");
        }
        break;
    case 3:
        {
            scoreSurface = SDL_LoadBMP("images/score3.bmp");
        }
        break;
    case 4:
        {
            scoreSurface = SDL_LoadBMP("images/score4.bmp");
        }
        break;
    case 5:
        {
            scoreSurface = SDL_LoadBMP("images/score5.bmp");
        }
        break;
    default:
        break;
    }

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
