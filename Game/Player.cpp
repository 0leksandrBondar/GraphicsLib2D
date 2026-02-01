#include "Player.h"

#include "GraphicsLib/Resource/ResourceManager.h"

Player::Player()
    : _sprite{ gfx2d::Sprite::create(
          gfx2d::ResourceManager::getInstance()->getShader("defaultShader")) }
{
    setSize(175, 175);

    _sprite->setColor(10,20,30);

    const auto texture = gfx2d::ResourceManager::getInstance()->getTexture("TrollAtlas");

    texture->addSubTexture("Gold", 37, 19, 21, 21);
    texture->addSubTexture("Silver", 84, 20, 64, 64);

    _sprite->setTexture(texture);
    _sprite->activateSubTexture("Gold");
}

void Player::update(const float deltaTime) {}