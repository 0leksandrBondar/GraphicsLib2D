#pragma once

#include "GraphicsLib/Graphics/GraphicsItem.h"

#include <memory>

namespace gfx2d
{
    class Shader;
    class Texture;

    using SpritePtr = std::shared_ptr<class Sprite>;

    class Sprite final : public GraphicsItem
    {
    public:
        explicit Sprite(const ShaderPtr& shader);
        Sprite(const ShaderPtr& shader, const std::filesystem::path& texturePath);

        static SpritePtr create(const ShaderPtr& shader);
        static SpritePtr create(const ShaderPtr& shader, const std::filesystem::path& texturePath);

        void setTextureRect(int x, int y, int w, int h);

    private:
        void buildMesh(float u1, float v1, float u2, float v2);

        void setupBuffers();
    };
} // namespace gfx2d
