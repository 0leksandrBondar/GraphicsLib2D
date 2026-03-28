#pragma once

#include "Game/Levels/Level.h"
#include "Game/Player/Player.h"

struct MapCell : public BaseGameObject
{
    gfx2d::GraphicsItem* getGraphicsItem() override { return sprite.get(); };

    gfx2d::SpritePtr sprite{ nullptr };
};

class Overworld final : public Level
{
public:
    Overworld();

public:
    void render() override;
    void initialize() override;
    void update(const float deltaTime) override;

private:
    void initializeCamera();
    void initializeMap() const;

    void updateCameraPosition(const float deltaTime) const;

private:
    std::shared_ptr<Scene> _scene{ nullptr };
    std::shared_ptr<Player> _player{ nullptr };
};
