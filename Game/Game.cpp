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
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(const float deltaTime) const
{
    update(deltaTime);
    render();
}

void Game::render() const
{
    _window->getRenderer()->render(_player->graphicsItem().get());
}

void Game::update(const float deltaTime) const
{
    handleMouseScroll(deltaTime);
    handleKeyboard(deltaTime);
    handleMouseClick(deltaTime);

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
