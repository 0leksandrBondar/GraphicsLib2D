#pragma once

#include "GraphicsLib/RawGraphics/Texture2D.h"

#include <unordered_map>

namespace gfx2d
{
    struct TextureRegion
    {
        TexturePtr texture;
        float u1, v1;
        float u2, v2;
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