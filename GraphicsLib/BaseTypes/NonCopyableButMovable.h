#pragma once

namespace gfx2d
{
    class NonCopyableButMovable
    {
    protected:
        NonCopyableButMovable() = default;
        ~NonCopyableButMovable() = default;

        NonCopyableButMovable(NonCopyableButMovable&&) = default;
        NonCopyableButMovable& operator=(NonCopyableButMovable&&) = default;

        NonCopyableButMovable(const NonCopyableButMovable&) = delete;
        NonCopyableButMovable& operator=(const NonCopyableButMovable&) = delete;
    };
} // namespace gfx2d