#pragma once

#include <chrono>

namespace gfx2d
{
    class Timer final
    {
    public:
        Timer();

        void update();

        [[nodiscard]] float getDeltaTime() const { return _deltaTime; }

    private:
        std::chrono::steady_clock::time_point _lastFrameTime{};
        float _deltaTime = 0.0f;
    };
} // namespace gfx2d