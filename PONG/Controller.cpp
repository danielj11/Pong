#include "Controller.h"

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 20

Controller::Controller()
{
    gWindow = NULL;
    renderer = SDL_CreateRenderer(gWindow, -1, 0);
    NyanTheSong = NULL;
    paddleOpp = true;
}

Controller::~Controller()
{
}

//Function that runs the game
void Controller::runGame()
{
    //Start up SDL and create window
	if( !initialize() )
	{
		cout << "Failed to initialize!"  << endl;
	}
	else
	{
	    //Player 1 paddle colors
        int colorChangeP1 = 0; //how long till color change (don't seizure it)
        int colorChoiceP1 = 0; //switch for colors

        //Player 2 paddle colors
        int colorChangeP2 = 8; //how long till color change (don't seizure it)
        int colorChoiceP2 = 3; //switch for colors

        //Music (NYAN!)
        NyanTheSong = NULL;
        NyanTheSong = Mix_LoadMUS("sounds/NyanTheSong.mp3");
        assert(NyanTheSong != NULL);

        SDL_Surface* BgSurface = NULL; //background surface
        SDL_Texture* Bg = NULL; //background

        BgSurface = SDL_LoadBMP("images/nyanbg.bmp");
        assert(BgSurface != NULL);

        Bg = SDL_CreateTextureFromSurface(renderer, BgSurface);
        assert(Bg != NULL);

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event gameEvents;
        SDL_Event NyanBGM;

        //Testing score display
        SDL_Surface* dash = NULL;
        SDL_Texture* dashTex = NULL;
        dash = SDL_LoadBMP("images/dash.bmp");
        SDL_Rect dashRect;
        dashRect.y = 0;
        dashRect.x = 374;
        dashRect.h = 52;
        dashRect.w = 43;
        dashTex = SDL_CreateTextureFromSurface(renderer,dash);

        SDL_Surface* scoreP1 = NULL;
        SDL_Texture* scoreP1Tex = NULL;
        scoreP1 = SDL_LoadBMP("images/score0.bmp");
        SDL_Rect P1ScoreRect;
        P1ScoreRect.y = 0;
        P1ScoreRect.x = 328;
        scoreP1Tex = SDL_CreateTextureFromSurface(renderer,scoreP1);
        P1ScoreRect.h = 52;
        P1ScoreRect.w = 43;

        SDL_Surface* scoreP2 = NULL;
        SDL_Texture* scoreP2Tex = NULL;
        scoreP2 = SDL_LoadBMP("images/score0.bmp");
        SDL_Rect P2ScoreRect;
        P2ScoreRect.y = 0;
        P2ScoreRect.x = 418;
        scoreP2Tex = SDL_CreateTextureFromSurface(renderer,scoreP2);
        P2ScoreRect.h = 52;
        P2ScoreRect.w = 43;
        //End of score display test

        //Set player one variables
        playerOne.setWidth(PADDLE_WIDTH);
        playerOne.setHeight(PADDLE_HEIGHT);
        playerOne.setPosX(20);
        playerOne.setPosY(230);

        //Set player two variables
        playerTwo.setWidth(PADDLE_WIDTH);
        playerTwo.setHeight(PADDLE_HEIGHT);
        playerTwo.setPosX(SCREEN_WIDTH - 40);
        playerTwo.setPosY(230);

        setPaddles(paddleOpp);//initial opponent paddle set

        //While game is still going
        while( !quit )
        {
            //Handle events on queue
            while(SDL_PollEvent(&NyanBGM) != 0)
            {
                //User requests quit
                if(NyanBGM.type == SDL_QUIT)
                {
                    quit = true;
                }

                //Handle input for the paddle(s)
                processInput(NyanBGM);
            }

            //Move the objects
            playerOne.move(SCREEN_HEIGHT, gameEvents);

            if (playerTwo.AIControlled)
            {
                playerTwo.moveAI(SCREEN_HEIGHT, playerOne.hitBox.y);
            }
            else
            {
                playerTwo.move(SCREEN_HEIGHT, gameEvents);
            }

            //Clear screen
            SDL_RenderCopy(renderer, Bg, NULL, NULL);
            SDL_RenderCopy(renderer,dashTex, NULL, &dashRect);
            SDL_RenderCopy(renderer,scoreP1Tex, NULL, &P1ScoreRect);
            SDL_RenderCopy(renderer,scoreP2Tex, NULL, &P2ScoreRect);

            colorChange(colorChangeP1, colorChoiceP1);

            SDL_RenderFillRect(renderer, &playerOne.hitBox);
            SDL_RenderDrawRect(renderer, &playerOne.hitBox);

            colorChange(colorChangeP2, colorChoiceP2);

            SDL_RenderFillRect(renderer, &playerTwo.hitBox);
            SDL_RenderDrawRect(renderer, &playerTwo.hitBox);

            //Update screen
            SDL_RenderPresent(renderer);
		}
	}

	//Close SDL
	closeGame();
}

bool Controller::initialize()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!" << endl;
		}

		//Create window
		gWindow = SDL_CreateWindow( "Nyan Pong!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError() << endl;
					success = false;
				}
				//Initialize SDL_mixer
				if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
				{
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }
			}
		}
	}
	return success;
}

void Controller::closeGame()
{
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

	//Free the music
    Mix_FreeMusic(NyanTheSong);
    NyanTheSong = NULL;

	//Quit SDL and SDL_Image
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

//universal events, not player specific
void Controller::processInput(SDL_Event& e)
{
    //will skip player input if not available
    playerOne.handleEvent(e);

    if (!playerTwo.AIControlled)
    {
        playerTwo.handleEventP2(e);
    }
    //playerTwo.handleEvent(e);

    if (e.type == SDL_KEYDOWN)
    {
        //pause and play music
        switch (e.key.keysym.sym)
        {
        case SDLK_m:
            //If there is no music playing
            if(Mix_PlayingMusic() == 0)
            {
                //Play the music
                Mix_PlayMusic(NyanTheSong, -1);
            }
            else //music is being played
            {
                //If the music is paused
                if( Mix_PausedMusic() == 1)
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                else //music is playing
                {
                    //Pause the music
                    Mix_PauseMusic();
                }
            }
            break;
        case SDLK_p:
            //The paddles are set here
            paddleOpp = !paddleOpp;
            setPaddles(paddleOpp); ///Change this to true for an AI paddle
            break;
        }
    }
}

//Sets paddle starting positions and determines if player 2 is AI controlled
void Controller::setPaddles(bool isAI)
{
    if (isAI)
    {
        playerTwo.AIControlled = true;
        playerTwo.speed = 5;
    }
    else
    {
        playerTwo.AIControlled = false;
        playerTwo.speed = 7;
    }
}

void Controller::colorChange(int& change, int& choice)
{
    //Make paddle the color of the rainbow (it switches every so often)
    if (change == 20)
    {
        switch (choice)
        {
        case 0: //red
            SDL_SetRenderDrawColor( renderer, 255, 0, 0, 0 );
            choice++;
            change = 0;
            break;
        case 1: //orange
            SDL_SetRenderDrawColor( renderer, 255, 128, 0, 0 );
            choice++;
            change = 0;
            break;
        case 2: //yellow
            SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
            choice++;
            change = 0;
            break;
        case 3: //green
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0 );
            choice++;
            change = 0;
            break;
        case 4: //blue
            SDL_SetRenderDrawColor( renderer, 0, 0, 255, 0 );
            choice++;
            change = 0;
            break;
        case 5: //purple
            SDL_SetRenderDrawColor( renderer, 204, 0, 204, 0 );
            choice = 0;
            change = 0;
            break;
        default: //if error pink, cause why not
            SDL_SetRenderDrawColor( renderer, 255, 192, 203, 0 );
            choice = 0;
        }
    }
    change++;
}
