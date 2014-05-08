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
		std::cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

		//Create window
		gWindow = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
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
					std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" <<  IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool Controller::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !ballTexture.loadFromFile( "images/dot.bmp", renderer) )
	{
		std::cout << "Failed to load dot texture!" << std::endl;
		success = false;
	}

	if( !paddleTexture.loadFromFile( "images/paddle.bmp", renderer) )
	{
		std::cout << "Failed to load dot texture!" << std::endl;
		success = false;
	}

	return success;
}

void Controller::closeGame()
{
	//Free loaded images
	ballTexture.free();
	paddleTexture.free();

	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL and SDL_Image
	IMG_Quit();
	SDL_Quit();
}

void Controller::renderObject(Object &r)
{
    paddleTexture.render(r.posX, r.posY, renderer);
}

void Controller::runGame()
{
    //Start up SDL and create window
	if( !initialize() )
	{
		std::cout << "Failed to initialize!"  << std::endl;
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event playerOneEvents;
			//SDL_Event playerTwoEvents;

			//The objects that will be on the screen
			Paddle playerOne(20,130); //20, 130
			playerOne.hitBox.x = 20;
			playerOne.hitBox.y = 100;
			/**playerOne.posX = 50; //50
			playerOne.posY = 200;//200
			playerOne.hitBox.w = playerOne.posX;
			playerOne.hitBox.h = playerOne.posY;*/



			//Set the wall
			SDL_Rect wall;
			wall.x = 300;
			wall.y = 40;
			wall.w = 40;
			wall.h = 400;

			std::cout << playerOne.posX << std::endl;
			std::cout << playerOne.posY << std::endl;
			std::cout << playerOne.hitBox.w << std::endl;
			std::cout << playerOne.hitBox.h << std::endl;

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
					/*std::cout << playerOne.posX << std::endl;
                    std::cout << playerOne.posY << std::endl;
                    std::cout << playerOne.hitBox.w << std::endl;
                    std::cout << playerOne.hitBox.h << std::endl;*/
                    /*wall.x += 5;
                    wall.y += 5;
                    wall.w = 40;
                    wall.h = 400;*/
				}

				//Move the objects
				playerOne.move(SCREEN_HEIGHT, playerOneEvents);
				//paddleTexture.render(50, 100, renderer);

				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				//Render wall
				SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderDrawRect( renderer, &wall );

				//Render objects
				//renderObject(playerOne);
				//std::cout << "test" <<std::endl;
				SDL_SetRenderDrawColor( renderer, 255, 192, 203, 100 );
				SDL_RenderFillRect(renderer, &playerOne.hitBox);
				SDL_RenderDrawRect( renderer, &playerOne.hitBox );

				//Update screen
				SDL_RenderPresent(renderer);


			}
		}
	}

	//Close SDL
	closeGame();

	std::cout << "Thanks for playing!" << std::endl;
}
