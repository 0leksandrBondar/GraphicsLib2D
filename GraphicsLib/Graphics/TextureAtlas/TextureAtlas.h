#pragma once

#include "GraphicsLib/RawGraphics/Texture.h"
#include "glm/vec2.hpp"

#include <unordered_map>

namespace gfx2d
{
    struct TextureRegion
    {
        TexturePtr texture;
        glm::vec2 leftBottomUV;
        glm::vec2 rightTopUV;
    };

    class TextureAtlas
    {
    public:
        explicit TextureAtlas(TexturePtr texture);

        void addRegion(const std::string& name, int x, int y, int w, int h);

        const TextureRegion& get(const std::string& name) const;

    private:
        TexturePtr _texture;
        std::unordered_map<std::string, TextureRegion> _regions;
    };
} // namespace gfx2d