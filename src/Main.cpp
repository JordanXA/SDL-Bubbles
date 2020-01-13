#include <iostream>
#include "SDL.h"

#include "Object.hpp"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int init();

SDL_Surface* loadImage(const char* filename) {
    //Load tyler
    SDL_Surface* newSurface = SDL_LoadBMP(filename);
    if( newSurface == NULL ) {
        printf( "Unable to load image tyler! SDL Error: %s\n", SDL_GetError() );
        return nullptr;
    }
    else {
        return newSurface;
    }
    
}

//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* gameSurface = NULL;

int main(int argc, char* args[]) {
    printf("Hello World!");

    init();

    SDL_Surface* tyler = loadImage("tyler.bmp");

    //Event handler
    SDL_Event e;

    bool quit;

    while(!quit) {
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }

        Object test;
        test.position.x = 5;

        //Fill the surface white
        SDL_FillRect( gameSurface, NULL, SDL_MapRGB( gameSurface->format, 0xCC, 0xCC, 0xFF ) );

        SDL_BlitSurface( tyler, NULL, gameSurface, NULL );

        //Update the surface
        SDL_UpdateWindowSurface( window );

    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

//Initialize SDL
int init() {

    int success = 0;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 1;
    }
    else {
    //Create window
    window = SDL_CreateWindow( "Bubbles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        success = 1;
    }

    //Get window surface
    gameSurface = SDL_GetWindowSurface( window );
    
    }

    return success;
}