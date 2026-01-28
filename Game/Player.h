#pragma once

#include "GraphicsLib/Graphics/Sprite/Sprite.h"

class Player
{
public:
    Player();

    void update(const float deltaTime);

    void setPosition(const float x, const float y) const { _sprite->setPosition(x, y); }
    void setPosition(glm::vec2 pos) const { _sprite->setPosition(pos); }
    void setSize(const float w, const float h) const { _sprite->setSize(w, h); }

    gfx2d::SpritePtr& graphicsItem() { return _sprite; }

private:
    gfx2d::SpritePtr _sprite{ nullptr };
};