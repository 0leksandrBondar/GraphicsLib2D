#pragma once

#include "Game/Core/Scene.h"
#include "GraphicsLib/Camera/Camera.h"

#include <memory>

enum class LevelType
{
    OverWorld,
};

class Level
{
public:
    Level() = default;
    explicit Level(LevelType type);
    virtual ~Level() = default;

    virtual void render() = 0;
    virtual void initialize() = 0;
    virtual void update(const float deltaTime) = 0;

protected:
    LevelType _levelType{ LevelType::OverWorld };
    std::shared_ptr<Scene> _scene{ nullptr };
    gfx2d::CameraPtr _camera{ nullptr };
};
