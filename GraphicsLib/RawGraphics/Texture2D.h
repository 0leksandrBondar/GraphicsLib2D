#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"

#include "glad/glad.h"
#include <filesystem>

namespace gfx2d
{

    using TexturePtr = std::shared_ptr<class Texture2D>;
    class Texture2D final : public NonCopyableButMovable
    {
    public:
        Texture2D() = default;
        explicit Texture2D(const std::filesystem::path& path);
        Texture2D(GLuint width, GLuint height, const unsigned char* data, size_t channels = 4,
                  GLenum filter = GL_LINEAR, GLenum wrapMode = GL_CLAMP_TO_EDGE);

        Texture2D& operator=(Texture2D&& other) noexcept;
        Texture2D(Texture2D&& other) noexcept { *this = std::move(other); }

        ~Texture2D() { glDeleteTextures(1, &_id); }

    public:
        static TexturePtr create(const std::filesystem::path& path);

        void setSmooth(bool smooth);

        void bind() const { glBindTexture(GL_TEXTURE_2D, _id); }
        void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

        [[nodiscard]] int getWidth() const { return _width; }
        [[nodiscard]] int getHeight() const { return _height; }
        [[nodiscard]] bool isSmooth() const { return _smooth; }

    private:
        void loadTexture(const std::filesystem::path& path);
        void initialize(const unsigned char* data, size_t channels = 4, GLenum filter = GL_LINEAR,
                        GLenum wrapMode = GL_CLAMP_TO_EDGE);

    private:
        GLuint _id{ 0 };
        GLenum _mode{ 0 };
        GLenum _format{ GL_RGB };

        bool _smooth{ false };

        int channels{ 0 };
        int _width{ 0 }, _height{ 0 };
    };

} // namespace gfx2d
