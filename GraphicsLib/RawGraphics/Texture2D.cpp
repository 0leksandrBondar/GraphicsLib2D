#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG
#include "stb_image.h"

namespace gfx2d
{
    Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
                         const size_t channels, const GLenum filter, const GLenum wrapMode)
        : _width(width), _height(height)
    {
        initialize(data, channels, filter, wrapMode);
    }

    TexturePtr Texture2D::create(const std::filesystem::path& path)
    {
        return std::make_shared<Texture2D>(path);
    }

    Texture2D::Texture2D(const std::filesystem::path& path) { loadTexture(path); }

    void Texture2D::loadTexture(const std::filesystem::path& path)
    {
        stbi_set_flip_vertically_on_load(true);

        unsigned char* pixels
            = stbi_load(path.string().c_str(), &_width, &_height, &channels, STBI_rgb_alpha);

        if (!pixels)
            throw std::runtime_error(stbi_failure_reason());

        initialize(pixels, 4, GL_NEAREST, GL_CLAMP_TO_EDGE);

        stbi_image_free(pixels);
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        glDeleteTextures(1, &_id);
        _id = other._id;
        _mode = other._mode;
        _width = other._width;
        _height = other._height;
        _smooth = other._smooth;
        return *this;
    }

    void Texture2D::setSmooth(const bool smooth)
    {
        _smooth = smooth;
        bind();

        const GLenum filter = smooth ? GL_LINEAR : GL_NEAREST;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        unbind();
    }

    void Texture2D::initialize(const unsigned char* data, const size_t channels,
                               const GLenum filter, const GLenum wrapMode)
    {
        if (!data)
            throw std::runtime_error("Texture2D: Invalid image data.");

        _format = channels == 4 ? GL_RGBA : GL_RGB;

        glGenTextures(1, &_id);
        bind();

        glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE,
                     data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        unbind();
    }

} // namespace gfx2d
