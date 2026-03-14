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
    _window->getCamera()->setZoom(2.5);
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(const float deltaTime) const
{
    update(deltaTime);
    render();
}

void Game::draw(gfx2d::GraphicsItem* item) const
{
    const auto shader = item->getShader();

    shader->use();

    // -------------------- vertex shader ----------------------------
    shader->setMatrix4("modelMat", item->getTransformMatrix());
    shader->setMatrix4("viewMat", _window->getCamera()->getViewMatrix());
    shader->setMatrix4("projectionMat", _window->getCamera()->getProjectionMatrix());

    // -------------------- fragment shader ----------------------------
    shader->setBool("useTexture", item->getShader() != nullptr);
    shader->setVector4("color", item->getColorVec4());

    gfx2d::Renderer::render(item);
}

void Game::render() const
{
    const gfx2d::math::AABB cameraBox = _window->getCamera()->getAABB();

    for (const auto& tile : _map)
    {
        const auto pos = tile->getPosition();
        const auto size = tile->getSize();

        const gfx2d::math::AABB tileBox = gfx2d::math::fromPositionSize(pos, size);

        if (!cameraBox.intersects(tileBox))
            continue;

        draw(tile.get());
    }

    draw(_player->graphicsItem().get());
}

void Game::update(const float deltaTime) const
{
    handleMouseScroll(deltaTime);
    handleMouseClick(deltaTime);

    // camera following to player
    glm::vec2 cameraPos = _window->getCamera()->getPosition();
    constexpr float smoothSpeed = 5.0f;
    cameraPos += (_player->graphicsItem()->getGlobalCenter() - cameraPos) * smoothSpeed * deltaTime;
    _window->getCamera()->setPosition(cameraPos);

    _player->update(deltaTime);
}

void Game::setupMap()
{
    const int mapWidth = 150;
    const int mapHeight = 150;
    const int tileWidth = 64;
    const int tileHeight = 32;

    _map.resize(mapWidth * mapHeight);

    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            const int index = y * mapWidth + x;

            _map[index]
                = gfx2d::Sprite::create(ResourceManager::getInstance()->getShader("defaultShader"));
            _map[index]->setTexture(ResourceManager::getInstance()->getTexture("Tiles"));
            _map[index]->setTextureRect(32 * 4, 16, 32, 16);
            _map[index]->setSize(tileWidth, tileHeight);

            float isoX = (x - y) * (tileWidth / 2.0f);
            float isoY = (x + y) * (tileHeight / 2.0f);

            _map[index]->setPosition({ isoX, isoY });
        }
    }
}

void Game::handleMouseScroll(float deltaTime) const
{
    if (const auto scroll = gfx2d::Input::consumeMouseScroll(); scroll.y != 0.0f)
    {
        float zoom = _window->getCamera()->getZoom();
        zoom *= (1.0f + scroll.y * 0.1f);
        zoom = std::clamp(zoom, 2.5f, 5.0f);
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
