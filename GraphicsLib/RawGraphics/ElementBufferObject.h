#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"
#include "glad/glad.h"

namespace gfx2d
{
    class ElementBufferObject final : public NonCopyableButMovable
    {
    public:
        ElementBufferObject();
        ~ElementBufferObject();

        ElementBufferObject(ElementBufferObject&& other) noexcept;
        ElementBufferObject& operator=(ElementBufferObject&& other) noexcept;

        void setData(const void* vertices, unsigned int size) const;

        void bind() const;
        void unbind() const;

    private:
        GLuint _id{ 0 };
    };
} // namespace gfx2d