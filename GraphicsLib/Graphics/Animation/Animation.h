#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

namespace gfx2d
{
    struct FrameData
    {
        int x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 };
    };

    class Animation final
    {
    public:
        explicit Animation(float frameTime = 0.1f, bool loop = false);

        void update(float deltaTime);

        void addAnimationFrame(int x, int y, int w, int h) { _frames.push_back({ x, y, w, h }); }

        FrameData getCurrentFrame() const;

        void reset();

        void setLoop(const bool loop) { _loop = loop; }
        [[nodiscard]] bool isFinished() const { return _isFinished; }
        void setFPS(const float fps);

        float getFrameTime() const { return _frameTime; }

    private:
        std::vector<FrameData> _frames;

        int _currentFrame{ 0 };
        float _timer{ 0.f };
        float _frameTime{ 0.1f };
        bool _loop{ true };
        bool _isFinished{ false };
    };

    using AnimationPtr = std::shared_ptr<Animation>;
} // namespace gfx2d
