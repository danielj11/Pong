#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>


//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* renderer);

    //Deallocates texture
    void free();

		//Renders texture at given point
    void render(int x, int y, SDL_Renderer* renderer);

		//Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* holdTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // TEXTURE_H
