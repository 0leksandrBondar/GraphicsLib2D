#include "Sprite.h"

#include "GraphicsLib/RawGraphics/Mesh.h"

namespace gfx2d
{

    Sprite::Sprite() { setupBuffers(); }

    Sprite::Sprite(Shader* shader, Texture2D* texture)
    {
        _shader = shader;
        _texture = texture;
        setupBuffers();
    }

    Sprite::Sprite(Shader* shader, Texture2D* texture, size_t width, size_t height)
    {
        _shader = shader;
        _texture = texture;
        setupBuffers();
    }

    SpritePtr Sprite::create() { return std::shared_ptr<Sprite>(new Sprite()); }
    SpritePtr Sprite::create(Shader* shader, Texture2D* texture)
    {
        return std::shared_ptr<Sprite>(new Sprite(shader, texture));
    }
    SpritePtr Sprite::create(Shader* shader, Texture2D* texture, size_t width, size_t height)
    {
        return std::shared_ptr<Sprite>(new Sprite(shader, texture, width, height));
    }

    void Sprite::setColor(glm::vec4 color) {}

    void Sprite::setShader(Shader* shader) { _shader = shader; }

    void Sprite::setTexture(Texture2D* texture) { _texture = texture; }

    void Sprite::setupBuffers()
    {
        const std::vector<Vertex> vertices = { { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
                                               { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
                                               { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
                                               { { 0.0f, 1.0f }, { 0.0f, 1.0f } } };
        const std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

        _meshes.emplace_back(Mesh(vertices, indices));
    }
} // namespace gfx2d