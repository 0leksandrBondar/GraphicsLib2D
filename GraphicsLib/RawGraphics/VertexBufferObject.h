#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"

#include "glad/glad.h"

namespace gfx2d
{
    class VertexBufferObject final : public NonCopyableButMovable
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        VertexBufferObject(VertexBufferObject&& other) noexcept;
        VertexBufferObject& operator=(VertexBufferObject&& other) noexcept;

        void setData(const void* vertices, unsigned int size) const;

        void bind() const;
        void unbind();

    private:
        GLuint _id{ 0 };
    };
} // namespace gfx2d