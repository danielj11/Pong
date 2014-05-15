#include "Controller.h"

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 20

Controller::Controller()
{
    gWindow = NULL;
    renderer = SDL_CreateRenderer(gWindow, -1, 0);
    NyanTheSong = NULL;
    paddleOpp = true;
    scoreP1 = 0;
    scoreP2 = 0;
    scoreDisplayP1.setRect(1);
    scoreDisplayP2.setRect(2);
    dash = NULL;
    dashTex = NULL;
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

        /**
            BALLS
        */
        bool timerSet = false;

        //Player 2 paddle colors
        int colorChangeP2 = 8; //how long till color change (don't seizure it)
        int colorChoiceP2 = 3; //switch for colors

        SDL_Surface* BgSurface = NULL; //background surface
        SDL_Texture* Bg = NULL; //background

        BgSurface = SDL_LoadBMP("images/nyanbg.bmp");
        assert(BgSurface != NULL);

        Bg = SDL_CreateTextureFromSurface(renderer, BgSurface);
        assert(Bg != NULL);

        //Music (NYAN!)
        NyanTheSong = NULL;
        NyanTheSong = Mix_LoadMUS("sounds/NyanTheSong.mp3");
        assert(NyanTheSong != NULL);

        //Main loop flag
        quit = false;

        //Event handler
        SDL_Event gameEvents;
        SDL_Event NyanBGM;

        //Testing score display
        dash = SDL_LoadBMP("images/dash.bmp");
        SDL_Rect dashRect;
        dashRect.y = 0;
        dashRect.x = 374;
        dashRect.h = 52;
        dashRect.w = 43;
        dashTex = SDL_CreateTextureFromSurface(renderer,dash);



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

        /**
            BALLS
        */

        Ball Nyan(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 8, -4);

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

                //Handle input for the player(s)
                processInput(NyanBGM);
            }

            //Move the objects
            playerOne.move(SCREEN_HEIGHT, gameEvents);

            if (playerTwo.AIControlled)
            {
                playerTwo.moveAI(SCREEN_HEIGHT, Nyan.hitBox.y);
            }
            else
            {
                playerTwo.move(SCREEN_HEIGHT, gameEvents);
            }

            //Clear screen
            SDL_RenderCopy(renderer, Bg, NULL, NULL);
            SDL_RenderCopy(renderer,dashTex, NULL, &dashRect);

            scoreDisplayP1.setImage(scoreP1, renderer);
            scoreDisplayP2.setImage(scoreP2, renderer);
            scoreDisplayP1.displayScore(renderer);
            scoreDisplayP2.displayScore(renderer);

            colorChange(colorChangeP1, colorChoiceP1);

            SDL_RenderFillRect(renderer, &playerOne.hitBox);
            SDL_RenderDrawRect(renderer, &playerOne.hitBox);

            colorChange(colorChangeP2, colorChoiceP2);

            SDL_RenderFillRect(renderer, &playerTwo.hitBox);
            SDL_RenderDrawRect(renderer, &playerTwo.hitBox);

            int ballMove = Nyan.move(SCREEN_HEIGHT, SCREEN_WIDTH, playerOne, playerTwo);

            SDL_RenderFillRect(renderer, &Nyan.hitBox);
            SDL_RenderDrawRect(renderer, &Nyan.hitBox);

            if (timerSet)
            {
                Nyan.timer();
                timerSet = false;
            }

            //move the ball
            if(ballMove == 1)
            {
                //P1 gets point
                scoreP1++;
                timerSet = true;
            }
            if(ballMove == 2)
            {
                //P2 gets point
                scoreP2++;
                timerSet = true;
            }

            if(scoreP1 == 9 || scoreP2 == 9)
            {
                quit = true;
                SDL_Surface* winSurface = NULL; //background surface
                SDL_Texture* winTexture = NULL; //background

                if (scoreP1 == 9)
                {
                    winSurface = SDL_LoadBMP("images/p1win.bmp");
                    assert(winSurface != NULL);
                    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
                    assert(winTexture != NULL);
                    SDL_RenderCopy(renderer, winTexture, NULL, NULL);
                }
                else
                {
                    winSurface = SDL_LoadBMP("images/p2win.bmp");
                    assert(winSurface != NULL);
                    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
                    assert(winTexture != NULL);
                    SDL_RenderCopy(renderer, winTexture, NULL, NULL);
                }

            }

            //Update screen
            SDL_RenderPresent(renderer);
		}
		SDL_Delay(1500);
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
        case SDLK_q:
            quit = true;
        }
    }
}

//Sets paddle starting positions and determines if player 2 is AI controlled
void Controller::setPaddles(bool isAI)
{
    if (isAI)
    {
        playerTwo.AIControlled = true;
        playerTwo.speed = 6;
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
