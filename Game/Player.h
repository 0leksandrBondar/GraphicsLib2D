#pragma once

#include "GraphicsLib/Graphics/Animation/Animator.h"
#include "GraphicsLib/Graphics/Sprite/Sprite.h"

class Player
{
public:
    Player();

    void update(float deltaTime) const;

    void setPosition(const float x, const float y) const { _sprite->setPosition(x, y); }
    void setPosition(const glm::vec2 pos) const { _sprite->setPosition(pos); }
    void setSize(const float w, const float h) const { _sprite->setSize(w, h); }

    gfx2d::SpritePtr& graphicsItem() { return _sprite; }

    void handleInput(const float deltaTime) const;

private:
    void setupAnimation() const;
    void setupWalkAnimation() const;

    void updateAnimation() const;

private:
    gfx2d::SpritePtr _sprite{ nullptr };
    gfx2d::AnimatorPtr _animator{ nullptr };
};