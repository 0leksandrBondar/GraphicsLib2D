#pragma once

#include "GraphicsLib/Graphics/GraphicsItem.h"

class BaseGameObject
{
public:
    BaseGameObject() = default;
    virtual ~BaseGameObject() = default;

public:
    void setSelection(const bool selection) { _isSelected = selection; };

    [[nodiscard]] bool isSelected() const { return _isSelected; };

    virtual void update(const float deltaTime) {};
    virtual gfx2d::GraphicsItem* getGraphicsItem() { return nullptr; }

protected:
    bool _isSelected{ false };
};
