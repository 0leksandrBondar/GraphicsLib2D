#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace gfx2d
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        void setPosition(const float x, const float y) { setPosition(glm::vec2(x, y)); }
        void setPosition(const glm::vec2& position);

        void setRotation(float rotation);

        void setScale(const float x, const float y) { setScale(glm::vec2(x, y)); }
        void setScale(const glm::vec2& scale);

        void move(float x, float y);

        void setSize(float width, float height);

        void zoom(float scaleFactor, glm::vec2 targetPos);

        [[nodiscard]] glm::vec2 getGlobalCenter() const noexcept;
        [[nodiscard]] glm::vec2 getLocalCenter() const noexcept;

        [[nodiscard]] int getWidth() const noexcept { return _size.x; }
        [[nodiscard]] int getHeight() const noexcept { return _size.y; }
        [[nodiscard]] glm::vec2 getSize() const noexcept { return _size; }
        [[nodiscard]] glm::vec2 getScale() const noexcept { return _scale; }
        [[nodiscard]] glm::vec2 getPosition() const noexcept { return _position; }
        [[nodiscard]] float getRotation() const noexcept { return _rotation; }
        [[nodiscard]] const glm::mat4& getTransformMatrix();

        void ignoreSize(const bool value) noexcept { _isIgnoreSize = value; }
        [[nodiscard]] bool isIgnoreSize() const noexcept { return _isIgnoreSize; }

    protected:
        bool _isIgnoreSize = false;

        float _rotation{};
        glm::vec2 _size{};
        glm::vec2 _scale{ 1.f };
        glm::vec2 _position{};

    private:
        glm::mat4 _modelMatrix{ 1.0f };
        bool _needsUpdate{ true };

        void updateTransform();
    };
} // namespace gfx2d
