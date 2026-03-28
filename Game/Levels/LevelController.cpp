#include "LevelController.h"

#include "Overworld/Overworld.h"

LevelController::LevelController()
{
    _levels[LevelType::OverWorld] = std::make_shared<Overworld>();
    _currentLevel = _levels[LevelType::OverWorld].get();
}

void LevelController::render() const
{
    if (_currentLevel != nullptr)
        _currentLevel->render();
}

void LevelController::update(const float deltaTime) const
{
    if (_currentLevel != nullptr)
        _currentLevel->update(deltaTime);
}

void LevelController::loadLevel(const LevelType level)
{
    if (const auto it = _levels.find(level); it != _levels.cend())
    {
        _currentLevel = it->second.get();
        _currentLevel->initialize();
    }
}