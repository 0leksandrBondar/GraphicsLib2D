#pragma once

#include "Game/Core/BaseGameObject.h"

#include <algorithm>
#include <memory>
#include <vector>

class Scene final
{
public:
    Scene() = default;
    ~Scene() = default;

public:
    void add(std::shared_ptr<BaseGameObject> object) { _objects.emplace_back(std::move(object)); }

    void remove(const std::shared_ptr<BaseGameObject>& obj) { std::erase(_objects, obj); }

    void clear() { _objects.clear(); }

    const std::vector<std::shared_ptr<BaseGameObject>>& getObjects() const { return _objects; }

private:
    std::vector<std::shared_ptr<BaseGameObject>> _objects;

};