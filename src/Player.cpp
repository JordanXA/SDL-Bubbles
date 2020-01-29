#include "Player.hpp"

void Player::inputUpdate(int inFlags) {
    Vector2f newVelocity {0,0};

    float speed = 0.04f;

    if(inFlags & INFLAG_UP) newVelocity.y -= speed;
    if(inFlags & INFLAG_DOWN) newVelocity.y += speed;
    if(inFlags & INFLAG_LEFT) newVelocity.x -= speed;
    if(inFlags & INFLAG_RIGHT) newVelocity.x += speed;

    setVelocity(newVelocity);

}
