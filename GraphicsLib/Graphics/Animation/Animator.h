#pragma once

#include "Animation.h"

#include <memory>
#include <unordered_map>

namespace gfx2d
{

    using AnimatorPtr = std::shared_ptr<class Animator>;

    class Animator final
    {
    public:
        Animator() = default;

        void update(const float deltaTime) const;

        static AnimatorPtr create() { return std::make_shared<Animator>(); }

        void play(const std::string& animationName);

        void addAnimationState(const std::string& animationName, const AnimationPtr& animation);

        FrameData getCurrentFrame() const;

        AnimationPtr getAnimation(const std::string& animationName) const;
        AnimationPtr getCurrentAnimation() const { return _currentAnimation; }

        const std::string& getAnimationName(const AnimationPtr& animation = nullptr) const;
        std::unordered_map<std::string, AnimationPtr>& getAnimations() { return _animations; }

    private:
        std::unordered_map<std::string, AnimationPtr> _animations;
        AnimationPtr _currentAnimation{ nullptr };
        std::string _currentState;
    };
} // namespace gfx2d