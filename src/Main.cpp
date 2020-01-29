#include <iostream>
#include <fstream>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"

#include "Drawable.hpp"
#include "Object.hpp"
#include "Player.hpp"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int init();

//variables global to this file:
    std::ofstream output;
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The renderer
    SDL_Renderer* renderer = NULL;

    bool quit;

SDL_Surface* imgToSurface( std::string path);
SDL_Texture* loadTexture( std::string path );
void renderDrawable(Drawable& obj);
void handleInput(SDL_Event& events);
int playerInput;

///stuff frm internet
//https://stackoverflow.com/questions/18682868/assigning-stdshared-ptr
    typedef std::shared_ptr<SDL_Texture> SharedTexture;

    inline SharedTexture make_shared(SDL_Texture* texture) {
        return SharedTexture(texture, SDL_DestroyTexture);
    }
///

//bool kUp, kDown, kLeft, kRight;

SharedTexture sansTexture = make_shared(loadTexture("sans.png"));
Player player = Player();


int main(int argc, char** argv) {
    SDL_Log("Hello World!");

    init();

    SDL_Log("peepee");

    //Event handler
    SDL_Event eventHandler;

    SharedTexture tylerTexture = make_shared(loadTexture("tyler.bmp"));
    Object tylerObject = Object();
    tylerObject.position = Vector2f{96,96};
    tylerObject.setTexture(tylerTexture, 96, 96);
    tylerObject.setVelocity(0.001f, 0);

    player.setTexture(sansTexture, 256, 256);
    player.position = Vector2f{256,256};

    while(!quit) {
        
        handleInput(eventHandler);

        player.inputUpdate(playerInput);

        tylerObject.tickMove();
        player.tickMove();

        //Clear screen
        SDL_RenderClear( renderer );

        renderDrawable(tylerObject);
        renderDrawable(player);

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

    SDL_RenderCopy( renderer, obj.getTexturePtr(), nullptr, &renderRect );
}


void handleInput(SDL_Event& events) {
        //Handle events on queue
        while( SDL_PollEvent( &events ) != 0 ) {
            //User requests quit
            if( events.type == SDL_QUIT ) {
                quit = true;
            }
            if (events.type == SDL_KEYDOWN ) {
                switch (events.key.keysym.sym) {
                    case SDLK_UP:
                    playerInput = playerInput | INFLAG_UP;
                    break;

                    case SDLK_DOWN:
                    kDown = true; //TODO: finish
                    break;

                    case SDLK_LEFT:
                    kLeft = true;
                    break;

                    case SDLK_RIGHT:
                    kRight = true;
                    break;
                }
            }

            if (events.type == SDL_KEYUP ) {
                switch (events.key.keysym.sym) {
                    case SDLK_UP:
                    kUp = false;
                    break;

                    case SDLK_DOWN:
                    kDown = false;
                    break;

                    case SDLK_LEFT:
                    kLeft = false;
                    break;

                    case SDLK_RIGHT:
                    kRight = false;
                    break;
                }
            }

        }
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

    //SDL_Log(extension.compare(".bmp"));

    if(extension.compare(".bmp") == 0)
        newSurface = SDL_LoadBMP(path.c_str());
    else if (extension.compare(".png") == 0)
        newSurface = IMG_Load(path.c_str());
    
    if( newSurface == NULL ) {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return nullptr;
    }
    else {
        return newSurface;
    }
}
