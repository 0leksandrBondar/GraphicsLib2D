#include "Game.h"

#include "GraphicsLib/Resource/ResourceManager.h"
#include "Player.h"

Game::Game()
    : _window{ gfx2d::Window::create(1200, 900, "gfx2d") }, _player{ std::make_shared<Player>() }
{
    loadDefaultResources();

    _background
        = gfx2d::Sprite::create(gfx2d::ResourceManager::getInstance()->getShader("defaultShader"));

    _background->setSize(300, 300);
    _player->setSize(150, 150);

    _background->setColor({ 122, 122, 122, 1 });

    _window->setOnFrameCallback([&](const float deltaTime) { onTickCallback(deltaTime); });

    _player->setPosition(_background->getGlobalCenter()
                         - _player->graphicsItem()->getLocalCenter());
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(float deltaTime) const
{
    _window->getRenderer()->render(_background.get());
    _window->getRenderer()->render(_player->graphicsItem().get());
}

void Game::loadDefaultResources()
{
    gfx2d::ResourceManager::getInstance()->loadShader("defaultShader", "Assets/Shaders/Vertex.vert",
                                                      "Assets/Shaders/Fragment.frag");
}