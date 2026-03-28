#pragma once

#include "Game/Core/BaseGameObject.h"
#include "GraphicsLib/Graphics/Sprite/Sprite.h"

class MapItem final : BaseGameObject
{
public:
    MapItem() = default;

public:
    gfx2d::GraphicsItem* getGraphicsItem() override { return _sprite.get(); };
    gfx2d::SpritePtr _sprite{ nullptr };
};

class Map
{
public:
    Map();

    std::vector<MapItem>& getMap() { return _map; }

    void initialize();

private:
    std::vector<MapItem> _map;
};