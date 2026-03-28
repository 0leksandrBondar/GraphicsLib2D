#pragma once
#include "Level.h"

#include <unordered_map>


class LevelController
{
public:
    LevelController();

    void render() const;
    void update(const float deltaTime) const;

    void loadLevel(LevelType level);

private:
    std::unordered_map<LevelType, std::shared_ptr<Level>> _levels;
    Level* _currentLevel{ nullptr };
};
