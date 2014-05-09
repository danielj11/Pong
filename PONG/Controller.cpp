#include "Controller.h"

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
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		//std::cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			//std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

		//Create window
		gWindow = SDL_CreateWindow( "Nyan Pong!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			//std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				//std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					//std::cout << "SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError() << std::endl;
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

	//Quit SDL and SDL_Image
	IMG_Quit();
	SDL_Quit();
}

void Controller::runGame()
{
    //Start up SDL and create window
	if( !initialize() )
	{
		//std::cout << "Failed to initialize!"  << std::endl;
	}
	else
	{
	    //paddleP1 colors
        int colorChangeP1 = 0; //how long till color change (don't seizure it)
        int colorChoiceP1 = 0; //switch for colors

        //paddleP2 colors
        int colorChangeP2 = 0; //how long till color change (don't seizure it)
        int colorChoiceP2 = 3; //switch for colors

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

        //The objects that will be on the screen
        Paddle playerOne(20,130); //20, 130
        playerOne.hitBox.x = 20;
        playerOne.hitBox.y = 100;

        //While game is still going
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &playerOneEvents ) != 0 )
            {
                //User requests quit
                if( playerOneEvents.type == SDL_QUIT )
                {
                    quit = true;
                }

                //Handle input for the paddle(s)
                playerOne.handleEvent(playerOneEvents);
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

            //Update screen
            SDL_RenderPresent(renderer);

            //inc color change counter
            colorChangeP1++;
		}
	}

	//Close SDL
	closeGame();
}
