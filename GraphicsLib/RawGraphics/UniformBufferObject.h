#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"

#include "glad/glad.h"

namespace gfx2d
{
    class UniformBufferObject final : public NonCopyableButMovable
    {
    public:
        UniformBufferObject();
        ~UniformBufferObject();

        void create(int size, GLuint bindingPoint);

        void bind() const;
        void unbind() const;

        void updateData(const void* data, int size, int offset = 0);

        GLuint getID() const { return _id; }

    private:
        GLuint _id = 0;
        GLuint _bindingPoint = 0;
        int _size = 0;
    };
} // namespace gfx2d