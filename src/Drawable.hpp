#include <memory>
#include <cmath>
#include "SDL.h"
#include "Vectors.hpp"

class Drawable {
    public:
        Vector2f position;
        Vector2i tempWH;
        std::shared_ptr<SDL_Texture> texture;
        Drawable() {
            position = Vector2f{0,0};
            tempWH = Vector2i{32,32};
        };
        void setTexture(std::shared_ptr<SDL_Texture> newTexture) {
            texture = newTexture;
        }
        SDL_Rect getRect() {
            return SDL_Rect{
            (int) std::round(position.x), (int) std::round(position.y), tempWH.x, tempWH.y
        };}
};