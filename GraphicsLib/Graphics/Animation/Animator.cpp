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
    }

    const std::string& Animator::getAnimationName(const AnimationPtr& animation) const
    {
        const AnimationPtr target = animation ? animation : _currentAnimation;

        if (!target)
            throw std::runtime_error("No current animation");

        for (const auto& [name, anim] : _animations)
        {
            if (anim == target)
                return name;
        }

        throw std::runtime_error("Animation not found in Animator");
    }


} // namespace gfx2d