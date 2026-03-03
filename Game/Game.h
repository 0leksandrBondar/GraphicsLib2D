#pragma once

#include "GraphicsLib/Graphics/Sprite/Sprite.h"
#include "GraphicsLib/Window/Window.h"

class Player;

class Game final
{
public:
    Game();

    void run() const;
    void onTickCallback(float deltaTime) const;

private:
    void draw(gfx2d::GraphicsItem* item) const;

    void render() const;
    void update(float deltaTime) const;

    void setupMap();
    void handleKeyboard(float deltaTime) const;
    void handleMouseScroll(float deltaTime) const;
    void handleMouseClick(float deltaTime) const;

private:
    gfx2d::WindowPtr _window{ nullptr };
    std::shared_ptr<Player> _player{ nullptr };

    std::vector<gfx2d::SpritePtr> _map;

    gfx2d::SpritePtr _tileMap{ nullptr };
};