#include "Controller.h"

#define DICKBUTT 100

Controller::Controller()
{
    gWindow = NULL;
    renderer = renderer = SDL_CreateRenderer(gWindow, -1, 0);
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

void Controller::runGame()
{
    //Start up SDL and create window
	if( !initialize() )
	{
		cout << "Failed to initialize!"  << endl;
	}
	else
	{
	    //paddleP1 colors
        int colorChangeP1 = 0; //how long till color change (don't seizure it)
        int colorChoiceP1 = 0; //switch for colors

        //paddleP2 colors
        int colorChangeP2 = 0; //how long till color change (don't seizure it)
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
        SDL_Event playerOneEvents;
        //SDL_Event playerTwoEvents;
        SDL_Event NyanBITCH;

        //The objects that will be on the screen
        playerOne.setWidth(20);
        playerOne.setHeight(DICKBUTT);
        playerOne.setPosX(20);
        playerOne.setPosY(DICKBUTT+130);

        playerTwo.setWidth(20);
        playerTwo.setHeight(DICKBUTT);
        playerTwo.setPosX(SCREEN_WIDTH - 40);
        playerTwo.setPosY(DICKBUTT+130);

        //While game is still going
        while( !quit )
        {
            //Handle events on queue
            while(SDL_PollEvent(&NyanBITCH) != 0)
            {
                //User requests quit
                if(NyanBITCH.type == SDL_QUIT)
                {
                    quit = true;
                }

                //Handle input for the paddle(s)
                processInput(NyanBITCH);
            }

            //Move the objects
            playerOne.move(SCREEN_HEIGHT, playerOneEvents);

            //Clear screen
            SDL_RenderCopy(renderer, Bg, NULL, NULL);

            //Make P1 paddle the color of the rainbow (it switches every so often)
            if (colorChangeP1 == 15)
            {
                switch (colorChoiceP1)
                {
                case 0: //red
                    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 0 );
                    colorChoiceP1++;
                    colorChangeP1 = 0;
                    break;
                case 1: //orange
                    SDL_SetRenderDrawColor( renderer, 255, 128, 0, 0 );
                    colorChoiceP1++;
                    colorChangeP1 = 0;
                    break;
                case 2: //yellow
                    SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
                    colorChoiceP1++;
                    colorChangeP1 = 0;
                    break;
                case 3: //green
                    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0 );
                    colorChoiceP1++;
                    colorChangeP1 = 0;
                    break;
                case 4: //blue
                    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 0 );
                    colorChoiceP1++;
                    colorChangeP1 = 0;
                    break;
                case 5: //purple
                    SDL_SetRenderDrawColor( renderer, 204, 0, 204, 0 );
                    colorChoiceP1 = 0;
                    colorChangeP1 = 0;
                    break;
                default: //if error pink, cause why not
                    SDL_SetRenderDrawColor( renderer, 255, 192, 203, 0 );
                    colorChoiceP1 = 0;
                }
            }
            SDL_RenderFillRect(renderer, &playerOne.hitBox);
            SDL_RenderDrawRect(renderer, &playerOne.hitBox);

            SDL_RenderFillRect(renderer, &playerTwo.hitBox);
            SDL_RenderDrawRect(renderer, &playerTwo.hitBox);

            //Update screen
            SDL_RenderPresent(renderer);

            //inc color change counter
            colorChangeP1++;
		}
	}

	//Close SDL
	closeGame();
}

//universal events, not player specific
void Controller::processInput(SDL_Event& e)
{
    //will skip player input if not available
    playerOne.handleEvent(e);
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
        }
    }
}
