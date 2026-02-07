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

void Game::onTickCallback(const float deltaTime) const
{
    update(deltaTime);

    _window->getRenderer()->render(_background.get());
    _window->getRenderer()->render(_player->graphicsItem().get());
}

void Game::update(const float deltaTime) const
{
    handleMouseScroll(deltaTime);
    handleKeyboard(deltaTime);

    _player->update(deltaTime);
}

void Game::handleKeyboard(const float deltaTime) const
{
    int speed = 300;
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::LShift))
        speed *= 2;
    else
        speed = 300;

    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::W))
        _window->getCamera()->move({ 0, -speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::A))
        _window->getCamera()->move({ -speed * deltaTime, 0 });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::S))
        _window->getCamera()->move({ 0, speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::D))
        _window->getCamera()->move({ speed * deltaTime, 0 });
}

void Game::handleMouseScroll(float deltaTime) const
{
    if (const auto scroll = gfx2d::Input::consumeMouseScroll(); scroll.y != 0.0f)
    {
        float zoom = _window->getCamera()->getZoom();
        zoom *= (1.0f + scroll.y * 0.1f);
        zoom = std::clamp(zoom, 0.1f, 5.0f);
        _window->getCamera()->setZoom(zoom);
    }
}

void Game::loadDefaultResources()
{
    gfx2d::ResourceManager::getInstance()->loadShader("defaultShader", "Assets/Shaders/Vertex.vert",
                                                      "Assets/Shaders/Fragment.frag");
    gfx2d::ResourceManager::getInstance()->loadTexture("PlayerAtlas", "Assets/Textures/player.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("CubeAtlas", "Assets/Textures/464.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("TrollAtlas",
                                                       "Assets/Textures/spr_attack_strip10.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("Skin", "Assets/Textures/1.png");
}