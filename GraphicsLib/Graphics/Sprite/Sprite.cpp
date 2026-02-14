#include "Sprite.h"

#include "GraphicsLib/RawGraphics/Mesh.h"

namespace gfx2d
{

    Sprite::Sprite(const ShaderPtr& shader, const std::filesystem::path& texturePath)
    {
        _shader = shader;
        _texture = Texture::create(texturePath);
        setupBuffers();
    }

    SpritePtr Sprite::create(const ShaderPtr& shader) { return std::make_shared<Sprite>(shader); }

    SpritePtr Sprite::create(const ShaderPtr& shader, const TexturePtr& texture)
    {
        return std::make_shared<Sprite>(shader, texture);
    }

    Sprite::Sprite(const ShaderPtr& shader)
    {
        _shader = shader;
        setupBuffers();
    }

    Sprite::Sprite(const ShaderPtr& shader, const TexturePtr& texture)
    {
        _shader = shader;
        _texture = texture;
        setupBuffers();
    }

    // Sprite::Sprite(const ShaderPtr& shader, const TextureRegion* textureRegion)
    // {
    //     _shader = shader;
    //     _texture = textureRegion->texture;
    //     buildMesh(textureRegion->u1, textureRegion->v1, textureRegion->u2, textureRegion->v2);
    // }

    SpritePtr Sprite::create(const ShaderPtr& shader, const std::filesystem::path& texturePath)
    {
        return std::make_shared<Sprite>(shader, texturePath);
    }

    void Sprite::setTextureRect(const FrameData data)
    {
        const float texW = static_cast<float>(_texture->getWidth());
        const float texH = static_cast<float>(_texture->getHeight());

        const float u1 = data.x / texW;
        const float u2 = (data.x + data.w) / texW;
        const float v1 = data.y / texH;
        const float v2 = (data.y + data.h) / texH;

        buildMesh(u1, v1, u2, v2);
    }

    void Sprite::setTextureRect(int x, int y, int w, int h)
    {
        const float texW = static_cast<float>(_texture->getWidth());
        const float texH = static_cast<float>(_texture->getHeight());

        const float u1 = x / texW;
        const float u2 = (x + w) / texW;
        const float v1 = y / texH;
        const float v2 = (y + h) / texH;

        buildMesh(u1, v1, u2, v2);
    }

    void Sprite::buildMesh(float u1, float v1, float u2, float v2)
    {
        _meshes.clear();

        const std::vector<Vertex> vertices = { { { 0.f, 0.f }, { u1, v1 } },
                                               { { 1.f, 0.f }, { u2, v1 } },
                                               { { 1.f, 1.f }, { u2, v2 } },
                                               { { 0.f, 1.f }, { u1, v2 } } };

        const std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

        _meshes.emplace_back(vertices, indices);
    }

    void Sprite::setupBuffers()
    {
        const std::vector<Vertex> vertices = { { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
                                               { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
                                               { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
                                               { { 0.0f, 1.0f }, { 0.0f, 1.0f } } };
        const std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

        _meshes.emplace_back(vertices, indices);
    }
} // namespace gfx2d
