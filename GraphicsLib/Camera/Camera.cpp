#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gfx2d
{
    Camera::Camera(const float viewportWidth, const float viewportHeight)
        : _viewport(viewportWidth, viewportHeight)
    {
        _projectionMatrix = glm::ortho(0.f, viewportWidth, viewportHeight, 0.f, -100.f, 100.f);
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
        updateProjectionMatrix(width, height);
        _dirty = true;
    }

    math::AABB Camera::getAABB() const
    {
        const glm::vec2 camPos = getPosition();
        const float zoom = getZoom();

        const float width = _viewport.x / zoom;
        const float height = _viewport.y / zoom;

        return { camPos.x - width * 0.5f, camPos.y - height * 0.5f, width, height };
    }

    const glm::mat4& Camera::getViewMatrix() const
    {
        if (_dirty)
            updateMatrix();
        return _viewMatrix;
    }

    const glm::mat4& Camera::getProjectionMatrix() const { return _projectionMatrix; }

    void Camera::updateProjectionMatrix(const int width, const int height) const
    {
        _projectionMatrix = glm::ortho(0.f, static_cast<float>(width), static_cast<float>(height),
                                       0.f, -100.f, 100.f);
    }

    glm::vec2 Camera::screenToWorld(const glm::vec2& screenPos) const
    {
        const glm::vec2 windowSize = { _viewport.x, _viewport.y };

        const float x = (2.0f * screenPos.x) / windowSize.x - 1.0f;
        const float y = 1.0f - (2.0f * screenPos.y) / windowSize.y;

        const auto clipCoords = glm::vec4(x, y, 0.0f, 1.0f);

        const glm::mat4 invVP = glm::inverse(getProjectionMatrix() * getViewMatrix());

        const glm::vec4 world = invVP * clipCoords;

        return glm::vec2(world.x, world.y);
    }

    glm::vec2 Camera::worldToScreen(const glm::vec2& worldPos) const
    {
        const auto world = glm::vec4(worldPos, 0.0f, 1.0f);

        const glm::mat4 vp = getProjectionMatrix() * getViewMatrix();

        const glm::vec4 clip = vp * world;

        const glm::vec3 ndc = glm::vec3(clip) / clip.w;

        glm::vec2 screen;
        screen.x = (ndc.x + 1.0f) * 0.5f * _viewport.x;
        screen.y = (1.0f - ndc.y) * 0.5f * _viewport.y;

        return screen;
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