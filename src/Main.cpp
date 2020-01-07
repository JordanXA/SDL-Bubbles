#include <iostream>
#include "SDL.h"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    printf("Hello World!");
    
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* tyler = NULL;

    //Load tyler
    tyler = SDL_LoadBMP( "tyler.bmp" );
    if( tyler == NULL )
    {
        printf( "Unable to load image tyler! SDL Error: %s\n", SDL_GetError() );
    }

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else {
        //Create window
        window = SDL_CreateWindow( "Bubbles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xCC, 0xCC, 0xFF ) );

        SDL_BlitSurface( tyler, NULL, screenSurface, NULL );

        //Update the surface
        SDL_UpdateWindowSurface( window );

        //Wait two seconds
        SDL_Delay( 5000 );

    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
