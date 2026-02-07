#include "Animator.h"

#include "spdlog/spdlog.h"

namespace gfx2d
{

    void Animator::update(const float deltaTime) const
    {
        if (_currentAnimation)
            _currentAnimation->update(deltaTime);
    }

    void Animator::play(const std::string& animationName)
    {
        if (_currentState == animationName)
            return;

        const auto it = _animations.find(animationName);
        if (it == _animations.end())
        {
            spdlog::error("Animation {} not found", animationName);
            return;
        }

        _currentState = animationName;
        _currentAnimation = it->second;
        _currentAnimation->reset();
    }

    void Animator::addAnimationState(const std::string& animationName,
                                     const AnimationPtr& animation)
    {
        _animations[animationName] = animation;
    }

    FrameData Animator::getCurrentFrame() const
    {
        if (!_currentAnimation)
            return {};

        return _currentAnimation->getCurrentFrame();
    }

    AnimationPtr Animator::getAnimation(const std::string& animationName) const
    {
        const auto it = _animations.find(animationName);
        if (it == _animations.end())
            return {};
        return it->second;
    };

} // namespace gfx2d