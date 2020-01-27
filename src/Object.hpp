#pragma once

#include "Drawable.hpp"
#include "Vectors.hpp"

class Object : public Drawable {
    //things objects do that drawables do not:
    //collision
    //
    public:

        Object() {
            velocity = {0,0};
        }

        Vector2f velocity;

        void setVelocity(float x, float y);
        
        //call every frame to move based on the object's velocity
        void tickMove();
};