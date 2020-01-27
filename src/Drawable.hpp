#pragma once

#include <memory>
#include <cmath>
#include "SDL.h"
#include "Vectors.hpp"

class Drawable {
    public:
        Drawable() {
            position = Vector2f{0,0};
            tempWH = Vector2i{32,32};
        };
        void setTexture(std::shared_ptr<SDL_Texture> newTexture, int width, int height) {
            texture = newTexture;
            tempWH.x = width;
            tempWH.y = height;
        }
        SDL_Rect getRect() {
            return SDL_Rect{
            (int) std::round(position.x), (int) std::round(position.y), tempWH.x, tempWH.y
        };}

        SDL_Texture* getTexturePtr() {
            return texture.get();
        }
        
        Vector2f position;
    protected:
        Vector2i tempWH; //TODO: set up textures automatically filling this in
        std::shared_ptr<SDL_Texture> texture;
        //TODO: in the future could support tilemaps and stuff

};