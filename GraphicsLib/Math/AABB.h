#pragma once
#include "glm/vec2.hpp"

namespace gfx2d::math
{
    struct AABB
    {
        float x;
        float y;
        float w;
        float h;

        [[nodiscard]] bool intersects(const AABB& other) const
        {
            return !(x > other.x + other.w || x + w < other.x || y > other.y + other.h
                     || y + h < other.y);
        }
    };

    inline AABB fromPositionSize(const glm::vec2& pos, const glm::vec2& size)
    {
        return { pos.x, pos.y, size.x, size.y };
    }
} // namespace gfx2d::math