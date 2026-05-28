#include "player.hpp"
extern char *appDir;

Player::Player() {
    texture = LoadTexture(TextFormat("%/assets/images/player.png", appDir));

    position.x = (GetScreenWidth() - texture.width) / 2.0f;
    position.y = (GetScreenHeight() - texture.height) -10.0f;

    speed = 150.0f;
}

Player::Player() {
    UnloadTexture(texture);
}

void Player::draw() const {
    DrawTexture(texture, position.x, position.y, RAYWHITE);
}