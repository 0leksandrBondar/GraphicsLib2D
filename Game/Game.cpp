#include "Game.h"

#include "Player/Player.h"
#include "ResourceManager/ResourceManager.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

Game::Game() : _window{ gfx2d::Window::create(1200, 900, "gfx2d") }
{
    ResourceManager::getInstance()->loadAllResources();
    _player = std::make_shared<Player>();
    _window->setOnFrameCallback([&](const float deltaTime) { onTickCallback(deltaTime); });
    setupMap();
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(const float deltaTime) const
{
    update(deltaTime);
    render();
}

void Game::render() const
{
    for (const auto& map : _map)
    {
        _window->getRenderer()->render(map.get());
    }
    _window->getRenderer()->render(_player->graphicsItem().get());
}

void Game::update(const float deltaTime) const
{
    handleMouseScroll(deltaTime);
    handleKeyboard(deltaTime);
    handleMouseClick(deltaTime);

    _player->update(deltaTime);
}

void Game::setupMap()
{
    const int mapWidth = 20;
    const int mapHeight = 20;
    const int tileSize = 32;

    _map.resize(mapWidth * mapHeight);

    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            int index = y * mapWidth + x;

            _map[index]
                = gfx2d::Sprite::create(ResourceManager::getInstance()->getShader("defaultShader"));

            _map[index]->setSize(tileSize, tileSize);
            _map[index]->setColor(gfx2d::DefColor::Cyan);

            _map[index]->setPosition({ static_cast<float>(x * tileSize + x * 10),
                                       static_cast<float>(y * tileSize + y * 10) });
        }
    }
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

void Game::handleMouseClick(float deltaTime) const
{
    const glm::vec2 mouseScreen = gfx2d::Input::getMousePosition();
    const glm::vec2 mouseWorld = _window->getCamera()->screenToWorld(mouseScreen);

    const glm::vec2 pos = _player->graphicsItem()->getPosition();
    const glm::vec2 size = _player->graphicsItem()->getSize();

    const bool isMouseOnPlayer = mouseWorld.x >= pos.x && mouseWorld.x <= pos.x + size.x
                                 && mouseWorld.y >= pos.y && mouseWorld.y <= pos.y + size.y;

    if (isMouseOnPlayer && gfx2d::Input::isMouseButtonJustPressed(gfx2d::Mouse::LeftButton))
        _player->setSelection(!_player->isSelected());
}
