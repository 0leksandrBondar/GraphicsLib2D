#pragma once
#include <algorithm>

namespace gfx2d
{
    struct Rect
    {
        Rect() = default;

        Rect(const float x, const float y, const float width, const float height)
            : x(x), y(y), width(width), height(height)
        {
        }

        float x{}, y{};
        float width{}, height{};

        [[nodiscard]] float left() const { return x; }
        [[nodiscard]] float right() const { return x + width; }
        [[nodiscard]] float top() const { return y; }
        [[nodiscard]] float bottom() const { return y + height; }

        [[nodiscard]] bool contains(const float px, const float py) const
        {
            return px >= left() && px <= right() && py >= top() && py <= bottom();
        }

        [[nodiscard]] bool contains(const Rect& other) const
        {
            return other.left() >= left() && other.right() <= right() && other.top() >= top()
                   && other.bottom() <= bottom();
        }

        [[nodiscard]] bool intersects(const Rect& other) const
        {
            return !(right() < other.left() || left() > other.right() || bottom() < other.top()
                     || top() > other.bottom());
        }

        [[nodiscard]] Rect intersected(const Rect& other) const
        {
            if (!intersects(other))
                return {};

            const float nx = std::max(left(), other.left());
            const float ny = std::max(top(), other.top());
            const float nr = std::min(right(), other.right());
            const float nb = std::min(bottom(), other.bottom());

            return { nx, ny, nr - nx, nb - ny };
        }
    };
} // namespace gfx2d