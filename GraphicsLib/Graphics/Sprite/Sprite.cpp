#include "Sprite.h"

#include "GraphicsLib/RawGraphics/Mesh.h"

namespace gfx2d
{

    Sprite::Sprite(Shader* shader, const std::filesystem::path& texturePath)
    {
        _shader = shader;
        _texture = Texture2D::create(texturePath);
        setupBuffers();
    }

    SpritePtr Sprite::create(Shader* shader, const std::filesystem::path& texturePath)
    {
        return std::shared_ptr<Sprite>(new Sprite(shader, texturePath));
    }

    void Sprite::setColor(glm::vec4 color) {}

    void Sprite::setShader(Shader* shader) { _shader = shader; }

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