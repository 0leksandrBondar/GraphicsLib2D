#pragma once

#include "GraphicsLib/Graphics/GraphicsItem.h"
#include "GraphicsLib/RawGraphics/Mesh.h"
#include "glm/vec4.hpp"

#include <memory>

namespace gfx2d
{
    class Shader;
    class Texture2D;

    using SpritePtr = std::shared_ptr<class Sprite>;

    class Sprite final : public GraphicsItem
    {
        Sprite(Shader* shader, const std::filesystem::path& texturePath);

    public:
        static SpritePtr create(Shader* shader, const std::filesystem::path& texturePath);

    public:
        void setColor(glm::vec4 color);
        void setShader(Shader* shader);

    private:
        void setupBuffers();
    };
} // namespace gfx2d