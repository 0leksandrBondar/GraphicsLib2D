#include "Overworld.h"

#include "Game/ResourceManager/ResourceManager.h"
#include "GraphicsLib/Graphics/Renderer/Renderer.h"

Overworld::Overworld() : _player{ std::make_shared<Player>() }
{
    _levelType = LevelType::OverWorld;
    _scene = std::make_shared<Scene>();
}

void Overworld::render()
{
    for (const auto gfxItem : _scene->getObjects())
    {
        const auto item = gfxItem->getGraphicsItem();
        const auto pos = item->getPosition();
        const auto size = item->getSize();

        if (!_camera->getRect().intersects(gfx2d::Rect(pos.x, pos.y, size.x, size.y)))
            continue;

        const auto shader = item->getShader();

        shader->use();

        // -------------------- vertex shader ----------------------------
        shader->setMatrix4("modelMat", item->getTransformMatrix());
        shader->setMatrix4("viewMat", _camera->getViewMatrix());
        shader->setMatrix4("projectionMat", _camera->getProjectionMatrix());

        // -------------------- fragment shader ----------------------------
        shader->setBool("useTexture", item->getTexture() != nullptr);
        shader->setVector4("color", item->getColorVec4());

        gfx2d::Renderer::render(item);
    }
}

void Overworld::initialize()
{
    initializeCamera();

    // Don't change order
    initializeMap();
    _scene->add(_player);
}

void Overworld::update(const float deltaTime)
{
    _player->update(deltaTime);
    updateCameraPosition(deltaTime);
}

void Overworld::initializeMap() const
{
    const int mapWidth = 150;
    const int mapHeight = 150;
    const int tileWidth = 64;
    const int tileHeight = 32;
    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            auto mapCell = std::make_shared<MapCell>();
            mapCell->sprite
                = gfx2d::Sprite::create(ResourceManager::getInstance()->getShader("defaultShader"));
            mapCell->sprite->setTexture(ResourceManager::getInstance()->getTexture("Tiles"));
            mapCell->sprite->setTextureRect(32 * 4, 16, 32, 16);
            mapCell->sprite->setSize(tileWidth, tileHeight);
            float isoX = (x - y) * (tileWidth / 2.0f);
            float isoY = (x + y) * (tileHeight / 2.0f);
            mapCell->sprite->setPosition({ isoX, isoY });
            _scene->add(mapCell);
        }
    }
}

void Overworld::updateCameraPosition(const float deltaTime) const
{
    glm::vec2 cameraPos = _camera->getPosition();
    constexpr float smoothSpeed = 5.0f;
    cameraPos
        += (_player->getGraphicsItem()->getGlobalCenter() - cameraPos) * smoothSpeed * deltaTime;
    _camera->setPosition(cameraPos);
}

void Overworld::initializeCamera()
{
    _camera = gfx2d::Camera::create(1200, 900);
    _camera->setZoom(2.5);
}