#include "Map.h"

#include "Game/ResourceManager/ResourceManager.h"

Map::Map() { initialize(); }


void Map::initialize()
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

            _map[index]._sprite
                = gfx2d::Sprite::create(ResourceManager::getInstance()->getShader("defaultShader"));
            _map[index]._sprite->setTexture(ResourceManager::getInstance()->getTexture("Tiles"));
            _map[index]._sprite->setTextureRect(32 * 4, 16, 32, 16);
            _map[index]._sprite->setSize(tileWidth, tileHeight);

            float isoX = (x - y) * (tileWidth / 2.0f);
            float isoY = (x + y) * (tileHeight / 2.0f);

            _map[index]._sprite->setPosition({ isoX, isoY });
        }
    }
}
