#include "Object.hpp"

void Object::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

void Object::tickMove() {
    position.x += velocity.x;
    position.y += velocity.y;
}