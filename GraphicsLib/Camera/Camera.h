#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

#include <memory>

namespace gfx2d
{

    using CameraPtr = std::shared_ptr<class Camera>;

    class Camera
    {
    public:
        Camera(float viewportWidth, float viewportHeight);

        static CameraPtr create(float viewportWidth, float viewportHeight);

        // Position
        void setPosition(const glm::vec2& pos);
        void move(const glm::vec2& delta);

        // Rotation (degrees)
        void setRotation(float degrees);
        void rotate(float delta);

        // Zoom
        void setZoom(float zoom);
        void zoom(float factor);

        // Viewport
        void setViewport(float width, float height);

        // Matrix
        const glm::mat4& getViewMatrix() const;
        const glm::mat4& getProjectionMatrix() const;

        void updateProjectionMatrix(int width, int height) const;

        // Getters
        glm::vec2 getPosition() const { return _position; }
        float getRotation() const { return _rotation; }
        float getZoom() const { return _zoom; }

    private:
        void updateMatrix() const;

        mutable glm::mat4 _viewMatrix{ 1.0f };
        mutable glm::mat4 _projectionMatrix{ 1.0f };
        mutable bool _dirty{ true };

        glm::vec2 _position{ 0.f, 0.f };
        float _rotation{ 0.f }; // degrees
        float _zoom{ 1.f };

        glm::vec2 _viewport{ 1.f, 1.f };
    };
} // namespace gfx2d