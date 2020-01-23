#include <iostream>
#include <fstream>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"

#include "Drawable.hpp"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int init();

std::ofstream output;
//The window we'll be rendering to
SDL_Window* window = NULL;
//The renderer
SDL_Renderer* renderer = NULL;

SDL_Surface* imgToSurface( std::string path);
SDL_Texture* loadTexture( std::string path );
void renderDrawable(Drawable& obj);

///stuff frm internet
//https://stackoverflow.com/questions/18682868/assigning-stdshared-ptr
typedef std::shared_ptr<SDL_Texture> SharedTexture;

inline SharedTexture make_shared(SDL_Texture* texture) {
    return SharedTexture(texture, SDL_DestroyTexture);
}
///

int main(int argc, char** argv) {
    SDL_Log("Hello World!");

    init();

    //Event handler
    SDL_Event e;
    bool quit;

    SharedTexture tylerTexture = make_shared(loadTexture("tyler.bmp"));
    Drawable tylerObject = Drawable();
    tylerObject.position = Vector2f{96,96};
    tylerObject.tempWH = Vector2i{96,96};
    tylerObject.setTexture(tylerTexture);

    while(!quit) {
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }

        //Clear screen
        SDL_RenderClear( renderer );

        renderDrawable(tylerObject);

        //Update screen
        SDL_RenderPresent( renderer );
        
        //SDL_Log("hey!");

    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    output.close();
    return 0;
}

void renderDrawable(Drawable& obj) {
    
    SDL_Rect renderRect = obj.getRect();

    SDL_RenderCopy( renderer, obj.texture.get(), nullptr, &renderRect );
}

//Initialize SDL
int init() {

    int success = 0;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 1;
    }
    else {
    //Create window
    window = SDL_CreateWindow( "Bubbles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if( window == NULL ) {
        SDL_Log( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        success = 1;
    }
    else {
        //Create renderer for window
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL ) {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Initialize renderer color
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
        }
    }
    
    }

    return success;
}


SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = imgToSurface( path );

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    if( newTexture == NULL )
    {
        SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

    return newTexture;
}

SDL_Surface* imgToSurface( std::string path) {
    //Load surface
    SDL_Surface* newSurface;
    size_t dotPos = path.find_last_of(".");
    std::string extension = path.substr(dotPos);

    printf(extension.c_str());

    newSurface = SDL_LoadBMP(path.c_str());
    if( newSurface == NULL ) {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return nullptr;
    }
    else {
        return newSurface;
    }
}
