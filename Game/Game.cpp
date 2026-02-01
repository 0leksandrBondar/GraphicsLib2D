#include "Game.h"

#include "GraphicsLib/Resource/ResourceManager.h"
#include "Player.h"

Game::Game() : _window{ gfx2d::Window::create(1200, 900, "gfx2d") }
{
    loadDefaultResources();
    _player = std::make_shared<Player>();

    _background
        = gfx2d::Sprite::create(gfx2d::ResourceManager::getInstance()->getShader("defaultShader"));

    _background->setSize(300, 300);
    _background->setColor(122, 122, 122);

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
    gfx2d::ResourceManager::getInstance()->loadTexture("PlayerAtlas", "Assets/Textures/player.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("CubeAtlas", "Assets/Textures/464.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("TrollAtlas",
                                                       "Assets/Textures/spr_attack_strip10.png");
}