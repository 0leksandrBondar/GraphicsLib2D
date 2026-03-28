#pragma once

#include "GraphicsLib/Window/Window.h"
#include "Levels/LevelController.h"

class Game final
{
public:
    Game();

    void run() const;
    void onTickCallback(float deltaTime) const;

private:
    gfx2d::WindowPtr _window{ nullptr };
    std::shared_ptr<LevelController> _levelController;
};