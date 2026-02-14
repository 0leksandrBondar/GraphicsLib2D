#include "Player.h"

#include "GraphicsLib/EventSystem/Input.h"
#include "GraphicsLib/Resource/ResourceManager.h"

Player::Player()
    : _sprite{ gfx2d::Sprite::create(gfx2d::ResourceManager::getInstance()->getShader(
                                         "defaultShader"),
                                     gfx2d::ResourceManager::getInstance()->getTexture(
                                         "Player_idle")) },
      _animator{ gfx2d::Animator::create() }
{
    setSize(300, 300);
    setupAnimation();
    _animator->play("idle_front");

    gfx2d::ResourceManager::getInstance()
        ->getShader("defaultShader")
        ->setBool("showDebugRect", true);
    gfx2d::ResourceManager::getInstance()
        ->getShader("defaultShader")
        ->setVector4("debugColor",{ 1.0f, 0.0f, 0.0f, 1.0f});
}

void Player::update(const float deltaTime)
{
    _animator->update(deltaTime);
    _sprite->setTextureRect(_animator->getCurrentFrame());

    updateAnimState();
    updateDirection();
    updateAnimation();

    static constexpr int speed = 100;

    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Up))
        _sprite->move(0, -speed * deltaTime);
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Down))
        _sprite->move(0, speed * deltaTime);
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Left))
        _sprite->move(-speed * deltaTime, 0);
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Right))
        _sprite->move(speed * deltaTime, 0);
}

void Player::setupWalkAnimation() const
{
    using AnimInfo = std::pair<const char*, int>;

    constexpr AnimInfo walkAnimations[]
        = { { "walk_left", 0 },    { "walk_right", 1 },     { "walk_front", 2 },
            { "walk_back", 3 },    { "walk_left_down", 4 }, { "walk_right_down", 5 },
            { "walk_left_up", 6 }, { "walk_right_up", 7 } };

    createAnimationsFromTable({ std::begin(walkAnimations), std::end(walkAnimations) }, 3);
}

void Player::setupIdleAnimation() const
{
    using AnimInfo = std::pair<const char*, int>;

    constexpr AnimInfo idleAnimations[]
        = { { "idle_left", 0 },    { "idle_right", 1 },     { "idle_front", 2 },
            { "idle_back", 3 },    { "idle_left_down", 4 }, { "idle_right_down", 5 },
            { "idle_left_up", 6 }, { "idle_right_up", 7 } };

    createAnimationsFromTable({ std::begin(idleAnimations), std::end(idleAnimations) }, 3);
}

void Player::createAnimationsFromTable(const std::vector<std::pair<std::string, int>>& anims,
                                       int frameCount) const
{
    constexpr int frameWidth = 48;
    constexpr int frameHeight = 48;

    for (const auto& [name, row] : anims)
    {
        auto anim = std::make_shared<gfx2d::Animation>();
        anim->setLoop(true);
        anim->setFPS(6);

        for (int i = 0; i < frameCount; ++i)
            anim->addAnimationFrame(i * frameWidth, row * frameHeight, frameWidth, frameHeight);

        _animator->addAnimationState(name, anim);
    }
}

void Player::updateDirection()
{
    if (_animType == AnimType::Idle)
        return;

    const bool up = gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Up);
    const bool down = gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Down);
    const bool left = gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Left);
    const bool right = gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Right);

    if (up && left)
        _moveDirection = Direction::Left_Up;
    else if (up && right)
        _moveDirection = Direction::Right_Up;
    else if (down && left)
        _moveDirection = Direction::Left_Down;
    else if (down && right)
        _moveDirection = Direction::Right_Down;

    else if (up)
        _moveDirection = Direction::Up;
    else if (down)
        _moveDirection = Direction::Down;
    else if (left)
        _moveDirection = Direction::Left;
    else if (right)
        _moveDirection = Direction::Right;
}


void Player::updateAnimState()
{
    const bool setWalkAnimType = gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Up)
                                 || gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Right)
                                 || gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Left)
                                 || gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Down)
                                 || gfx2d::Input::isKeyPressed(gfx2d::Keyboard::Up);
    if (setWalkAnimType)
        _animType = AnimType::Walk;
    else
        _animType = AnimType::Idle;

    updateTextureDependsOfAnimState();
}

void Player::updateTextureDependsOfAnimState() const
{
    if (_animType == AnimType::Idle
        && _sprite->getTexture()
               != gfx2d::ResourceManager::getInstance()->getTexture("Player_idle"))
    {
        _sprite->setTexture(gfx2d::ResourceManager::getInstance()->getTexture("Player_idle"));
    }
    else if (_animType == AnimType::Walk
             && _sprite->getTexture()
                    != gfx2d::ResourceManager::getInstance()->getTexture("Player_walk"))
    {
        _sprite->setTexture(gfx2d::ResourceManager::getInstance()->getTexture("Player_walk"));
    }
}

void Player::setupAnimation() const
{
    setupIdleAnimation();
    setupWalkAnimation();
}

void Player::updateAnimation() const
{
    if (_animType == AnimType::Idle)
    {
        if (_moveDirection == Direction::Up)
            _animator->play("idle_back");
        else if (_moveDirection == Direction::Right)
            _animator->play("idle_right");
        else if (_moveDirection == Direction::Left)
            _animator->play("idle_left");
        else if (_moveDirection == Direction::Down)
            _animator->play("idle_front");
        else if (_moveDirection == Direction::Right_Up)
            _animator->play("idle_right_up");
        else if (_moveDirection == Direction::Left_Up)
            _animator->play("idle_left_up");
        else if (_moveDirection == Direction::Left_Down)
            _animator->play("idle_left_down");
        else if (_moveDirection == Direction::Right_Down)
            _animator->play("idle_right_down");
    }
    else
    {
        if (_moveDirection == Direction::Up)
            _animator->play("walk_back");
        else if (_moveDirection == Direction::Right)
            _animator->play("walk_right");
        else if (_moveDirection == Direction::Left)
            _animator->play("walk_left");
        else if (_moveDirection == Direction::Down)
            _animator->play("walk_front");
        else if (_moveDirection == Direction::Right_Up)
            _animator->play("walk_right_up");
        else if (_moveDirection == Direction::Left_Up)
            _animator->play("walk_left_up");
        else if (_moveDirection == Direction::Left_Down)
            _animator->play("walk_left_down");
        else if (_moveDirection == Direction::Right_Down)
            _animator->play("walk_right_down");
    }
}
