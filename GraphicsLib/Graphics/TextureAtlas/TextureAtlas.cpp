#include "TextureAtlas.h"

namespace gfx2d
{
    TextureAtlas::TextureAtlas(TexturePtr texture) : _texture(std::move(texture)) {}

    void TextureAtlas::addRegion(const std::string& name, const int x, const int y, const int w,
                                 const int h)
    {
        const float texW = static_cast<float>(_texture->getWidth());
        const float texH = static_cast<float>(_texture->getHeight());

        // stb flip fix
        const float u1 = x / texW;
        const float u2 = (x + w) / texW;

        const float v2 = 1.f - y / texH;
        const float v1 = 1.f - (y + h) / texH;

        _regions[name] = TextureRegion{ _texture, u1, v1, u2, v2 };
    }

    const TextureRegion& TextureAtlas::get(const std::string& name) const
    {
        return _regions.at(name);
    }

} // namespace gfx2d