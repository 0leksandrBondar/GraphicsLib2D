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
        Sprite();
        Sprite(Shader* shader, Texture2D* texture);
        Sprite(Shader* shader, Texture2D* texture, size_t width, size_t height);

    public:
        static SpritePtr create();
        static SpritePtr create(Shader* shader, Texture2D* texture);
        static SpritePtr create(Shader* shader, Texture2D* texture, size_t width, size_t height);

    public:
        void setColor(glm::vec4 color);
        void setShader(Shader* shader);
        void setTexture(Texture2D* texture);

    private:
        void setupBuffers();
    };
} // namespace gfx2d