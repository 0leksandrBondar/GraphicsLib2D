#include "Transformable.h"

#include "glm/ext/matrix_transform.hpp"

namespace gfx2d
{
    void Transformable::setPosition(const glm::vec2& position)
    {
        _position = position;
        _needsUpdate = true;
    }

    void Transformable::setRotation(const float rotation)
    {
        _rotation = rotation;
        _needsUpdate = true;
    }

    void Transformable::setScale(const glm::vec2& scale)
    {
        _scale = scale;
        _needsUpdate = true;
    }

    void Transformable::setOrigin(const glm::vec2& origin)
    {
        _origin = origin;
        _needsUpdate = true;
        _originManuallySet = true;
    }

    void Transformable::setOriginToCenter()
    {
        _origin = _size * 0.5f;
        _originManuallySet = false;
        _needsUpdate = true;
    }

    void Transformable::move(const float x, const float y)
    {
        _position += glm::vec2(x, y);
        _needsUpdate = true;
    }

    void Transformable::setSize(float width, float height)
    {
        _size = { width, height };

        if (!_originManuallySet)
        {
            _origin = _size * 0.5f;
        }

        _needsUpdate = true;
    }
    void Transformable::zoom(const float scaleFactor, const glm::vec2 targetPos)
    {
        _scale *= scaleFactor;

        const glm::vec2 deltaPosition = (1.0f - scaleFactor) * (targetPos - _position);
        _position += deltaPosition;

        _needsUpdate = true;
    }

    glm::vec2 Transformable::getGlobalCenter() const noexcept
    {
        return _position + (_size * _scale) * 0.5f;
    }

    glm::vec2 Transformable::getLocalCenter() const noexcept { return (_size * _scale) * 0.5f; }

    const glm::mat4& Transformable::getTransformMatrix()
    {
        if (_needsUpdate)
            updateTransform();

        return _modelMatrix;
    }

    void Transformable::updateTransform()
    {
        const glm::vec2 size = _isIgnoreSize ? glm::vec2(1.f) : _size;
        const glm::vec2 scaledSize = size * _scale;

        // 1. Scale
        const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaledSize, 1.0f));

        // 2. Rotation around origin
        glm::mat4 rotationMatrix(1.0f);

        if (_rotation != 0.0f)
        {
            rotationMatrix
                = glm::translate(glm::mat4(1.0f), glm::vec3(_origin, 0.0f))
                  * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.f, 0.f, 1.f))
                  * glm::translate(glm::mat4(1.0f), glm::vec3(-_origin, 0.0f));
        }

        // 3. Translation
        const glm::mat4 translationMatrix
            = glm::translate(glm::mat4(1.0f), glm::vec3(_position, 0.0f));

        _modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        _needsUpdate = false;
    }
} // namespace gfx2d