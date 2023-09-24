#include "Player.h"
#include <SDL2/SDL_timer.h>
#include "../Graphics/TextureManager.h"

Player::Player(Properties *props) : Character(props)
{
    row = 1;
    frameCount = 4;
    animSpeed = 80;

}

Player::~Player()
{
}

void Player::draw()
{
    TextureManager::getInstance()->drawFrame(textureId, transform->x, transform->y, width, height, row, frame);
}

void Player::update( float dt ){
    frame = ( SDL_GetTicks() / animSpeed ) % frameCount;
    cout << frame << endl;
}


