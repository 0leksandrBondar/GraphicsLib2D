#pragma once

#include "GraphicsLib/Graphics/Animation/Animator.h"
#include "GraphicsLib/Graphics/Sprite/Sprite.h"

enum class AnimType
{
    Walk,
    Idle
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right,
    Right_Up,
    Right_Down,
    Left_Up,
    Left_Down,
};

class Player
{
public:
    Player();

    void update(float deltaTime);

    void setPosition(const float x, const float y) const { _sprite->setPosition(x, y); }
    void setPosition(const glm::vec2 pos) const { _sprite->setPosition(pos); }
    void setSize(const float w, const float h) const { _sprite->setSize(w, h); }


    gfx2d::SpritePtr& graphicsItem() { return _sprite; }

private:
    void setupAnimation() const;
    void updateAnimation() const;
    void setupWalkAnimation() const;
    void setupIdleAnimation() const;

    void createAnimationsFromTable(const std::vector<std::pair<std::string, int>>& anims,
                                   int frameCount) const;

    void updateDirection();
    void updateAnimState();
    void updateTextureDependsOfAnimState() const;

private:
    gfx2d::SpritePtr _sprite{ nullptr };
    gfx2d::AnimatorPtr _animator{ nullptr };
    AnimType _animType{ AnimType::Idle };
    Direction _moveDirection{ Direction::Up };
};