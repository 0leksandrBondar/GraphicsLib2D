#pragma once
#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"
#include "glad/glad.h"

#include <memory>

namespace gfx2d
{

    using RawTexturePtr = std::shared_ptr<class RawTexture>;

    class RawTexture final : public NonCopyableButMovable
    {
    public:
        RawTexture(int width, int height, const unsigned char* data, int channels = 4);

    public:
        static std::shared_ptr<RawTexture> create(int width, int height, const unsigned char* data,
                                                  int channels = 4);

        ~RawTexture() { glDeleteTextures(1, &_id); }

        void setSmooth(bool smooth) const;

        void bind() const { glBindTexture(GL_TEXTURE_2D, _id); }
        static void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    private:
        GLuint _id;
    };
} // namespace gfx2d