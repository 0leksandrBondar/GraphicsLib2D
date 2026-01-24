#include "Sprite.h"

#include "GraphicsLib/RawGraphics/Mesh.h"

namespace gfx2d
{

    Sprite::Sprite(ShaderPtr shader, const std::filesystem::path& texturePath)
    {
        _shader = shader;
        _texture = Texture2D::create(texturePath);
        setupBuffers();
    }

    SpritePtr Sprite::create(ShaderPtr shader) { return std::make_shared<Sprite>(shader); }

    Sprite::Sprite(ShaderPtr shader)
    {
        _shader = shader;
        setupBuffers();
    }

    Sprite::Sprite(ShaderPtr shader, const TextureRegion* textureRegion)
    {
        _shader = shader;
        _texture = textureRegion->texture;
        buildMesh(textureRegion->u1, textureRegion->v1, textureRegion->u2, textureRegion->v2);
    }

    SpritePtr Sprite::create(ShaderPtr shader, const std::filesystem::path& texturePath)
    {
        return std::make_shared<Sprite>(shader, texturePath);
    }
    SpritePtr Sprite::create(ShaderPtr shader, const TextureRegion* textureRegion)
    {
        return std::make_shared<Sprite>(shader, textureRegion);
    }

    void Sprite::setColor(glm::vec4 color)
    {
        _color = { color.x / 255, color.y / 255, color.z / 255, color.w };
    }

    void Sprite::setShader(ShaderPtr shader) { _shader = shader; }

    void Sprite::buildMesh(const float u1, const float v1, const float u2, const float v2)
    {
        const std::vector<Vertex> vertices = { { { 0.f, 0.f }, { u1, v1 } },
                                               { { 1.f, 0.f }, { u2, v1 } },
                                               { { 1.f, 1.f }, { u2, v2 } },
                                               { { 0.f, 1.f }, { u1, v2 } } };
        const std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };
        _meshes.emplace_back(Mesh(vertices, indices));
    }

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
