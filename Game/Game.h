#pragma once

#include "GraphicsLib/Graphics/Renderer/Renderer.h"
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
    static void loadDefaultResources();

private:
    gfx2d::WindowPtr _window{ nullptr };
    gfx2d::RendererPtr _renderer{ nullptr };
    gfx2d::SpritePtr _background{ nullptr };

    std::shared_ptr<Player> _player{ nullptr };
};