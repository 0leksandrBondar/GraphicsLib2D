#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"

#include "glad/glad.h"
#include "glm/vec2.hpp"

#include <filesystem>
#include <unordered_map>

namespace gfx2d
{

    using TexturePtr = std::shared_ptr<class Texture>;

    class Texture final : public NonCopyableButMovable
    {
    public:
        Texture() = default;
        explicit Texture(const std::filesystem::path& path);
        Texture(GLuint width, GLuint height, const unsigned char* data, size_t channels = 4,
                GLenum filter = GL_LINEAR, GLenum wrapMode = GL_CLAMP_TO_EDGE);

        Texture& operator=(Texture&& other) noexcept;
        Texture(Texture&& other) noexcept { *this = std::move(other); }

        ~Texture() { glDeleteTextures(1, &_id); }

    public:
        static TexturePtr create(const std::filesystem::path& path);

        void setSmooth(bool smooth);

        void bind() const { glBindTexture(GL_TEXTURE_2D, _id); }
        static void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

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
