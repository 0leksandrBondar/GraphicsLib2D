#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gfx2d
{
    Camera::Camera(const float viewportWidth, const float viewportHeight)
        : _viewport(viewportWidth, viewportHeight)
    {
    }

    CameraPtr Camera::create(float viewportWidth, float viewportHeight)
    {
        return std::make_shared<Camera>(viewportWidth, viewportHeight);
    }

    void Camera::setPosition(const glm::vec2& pos)
    {
        _position = pos;
        _dirty = true;
    }

    void Camera::move(const glm::vec2& delta)
    {
        _position += delta;
        _dirty = true;
    }

    void Camera::setRotation(const float degrees)
    {
        _rotation = degrees;
        _dirty = true;
    }

    void Camera::rotate(const float delta)
    {
        _rotation += delta;
        _dirty = true;
    }

    void Camera::setZoom(const float zoom)
    {
        _zoom = zoom;
        _dirty = true;
    }

    void Camera::zoom(const float factor)
    {
        _zoom *= factor;
        _dirty = true;
    }

    void Camera::setViewport(float width, float height)
    {
        _viewport = { width, height };
        _dirty = true;
    }

    const glm::mat4& Camera::getViewMatrix() const
    {
        if (_dirty)
            updateMatrix();
        return _viewMatrix;
    }

    void Camera::updateMatrix() const
    {
        glm::mat4 view(1.0f);

        // 1️⃣ move world to screen center
        view = glm::translate(view, glm::vec3(_viewport.x * 0.5f, _viewport.y * 0.5f, 0.f));

        // 2️⃣ rotate world opposite to camera
        view = glm::rotate(view, glm::radians(-_rotation), glm::vec3(0.f, 0.f, 1.f));

        // 3️⃣ zoom
        view = glm::scale(view, glm::vec3(_zoom, _zoom, 1.f));

        // 4️⃣ move world opposite to camera position
        view = glm::translate(view, glm::vec3(-_position, 0.f));

        _viewMatrix = view;
        _dirty = false;
    }
} // namespace gfx2d