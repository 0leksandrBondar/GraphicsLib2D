#pragma once

#include "GraphicsLib/Graphics/GraphicsItem.h"
#include "GraphicsLib/Graphics/TextureAtlas/TextureAtlas.h"
#include "glm/vec4.hpp"

#include <memory>

namespace gfx2d
{
    class Shader;
    class Texture2D;

    using SpritePtr = std::shared_ptr<class Sprite>;

    class Sprite final : public GraphicsItem
    {
    public:
        Sprite(Shader* shader, const std::filesystem::path& texturePath);
        Sprite(Shader* shader, const TextureRegion* textureRegion);

        static SpritePtr create(Shader* shader, const std::filesystem::path& texturePath);
        static SpritePtr create(Shader* shader, const TextureRegion* textureRegion);

    public:
        void setColor(glm::vec4 color);
        void setShader(Shader* shader);

    private:
        void buildMesh(float u1, float v1, float u2, float v2);

        void setupBuffers();
    };
} // namespace gfx2d