#include "Animation.h"

#include "spdlog/spdlog.h"

namespace gfx2d
{

    Animation::Animation(const float frameTime, const bool loop)
        : _frameTime(frameTime), _loop(loop)
    {
    }
    void Animation::update(const float deltaTime)
    {
        if (_frames.empty() || _isFinished)
            return;

        _timer += deltaTime;

        while (_timer >= _frameTime)
        {
            _timer -= _frameTime;
            _currentFrame++;

            if (_currentFrame >= _frames.size())
            {
                if (_loop)
                {
                    _currentFrame = 0;
                    _isFinished = false;
                }
                else
                {
                    _currentFrame = static_cast<int>(_frames.size() - 1);
                    _isFinished = true;
                }
            }
        }
    }
    FrameData Animation::getCurrentFrame() const
    {
        if (_frames.empty())
        {
            spdlog::error("Animation has no frames");
            return {};
        }

        return _frames[_currentFrame];
    }

    void Animation::reset()
    {
        _currentFrame = 0;
        _timer = 0.f;
        _isFinished = false;
    }

    void Animation::setFPS(const float fps)
    {
        if (fps <= 0.f)
            throw std::logic_error("FPS must be > 0");
        _frameTime = 1.0f / fps;
    }
} // namespace gfx2d