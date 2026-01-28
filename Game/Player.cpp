#include "Player.h"

#include "GraphicsLib/Resource/ResourceManager.h"

Player::Player()
    : _sprite{ gfx2d::Sprite::create(
          gfx2d::ResourceManager::getInstance()->getShader("defaultShader")) }
{
    _sprite->setColor({ 120, 180, 230, 1 });
}

void Player::update(const float deltaTime) {}