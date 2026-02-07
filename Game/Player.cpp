#include "Player.h"

#include "GraphicsLib/EventSystem/Input.h"
#include "GraphicsLib/Resource/ResourceManager.h"

Player::Player()
    : _sprite{ gfx2d::Sprite::create(
          gfx2d::ResourceManager::getInstance()->getShader("defaultShader")) },
      _animator{ gfx2d::Animator::create() }
{
    setSize(300, 300);
    setupAnimation();
    const auto texture = gfx2d::ResourceManager::getInstance()->getTexture("Skin");

    _sprite->setTexture(texture);
}

void Player::update(float deltaTime) const
{
    _animator->update(deltaTime);
    handleInput(deltaTime);

    updateAnimation();
}

void Player::setupWalkAnimation() const
{
    const auto walkAnimationState = std::make_shared<gfx2d::Animation>();

    constexpr int frameWidth = 80;
    constexpr int frameHeight = 64;
    constexpr int frameCount = 8;

    constexpr int startY = frameHeight * 2; // 2 - this is second row in atlas

    for (int i = 0; i < frameCount; ++i)
    {
        const int x = i * frameWidth;
        constexpr int y = startY;

        walkAnimationState->addAnimationFrame(x, y, frameWidth, frameHeight);
    }

    _animator->addAnimationState("walk", walkAnimationState);
    walkAnimationState->setLoop(true);
}

void Player::handleInput(const float deltaTime) const
{
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Space))
        _animator->play("walk");
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::RShift))
        _animator->getAnimation("walk")->reset();

}

void Player::setupAnimation() const { setupWalkAnimation(); }

void Player::updateAnimation() const
{
    // TODO: (point to optimization) we need to check previous FrameData and if data is the same do
    // nothing
    //TODO: use in Texture class FrameData instead of SubTexture
    const gfx2d::FrameData data = _animator->getCurrentFrame();
    _sprite->setTextureRect(data.x, data.y, data.w, data.h);
}