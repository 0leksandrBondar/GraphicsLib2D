#include "Game.h"

#include "ResourceManager/ResourceManager.h"

Game::Game() : _window{ gfx2d::Window::create(1200, 900, "gfx2d") }
{
    ResourceManager::getInstance()->loadAllResources();
    _window->setOnFrameCallback([&](const float deltaTime) { onTickCallback(deltaTime); });
    _levelController = std::make_shared<LevelController>();
    _levelController->loadLevel(LevelType::OverWorld);
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(const float deltaTime) const
{
    _levelController->update(deltaTime);
    _levelController->render();
}

