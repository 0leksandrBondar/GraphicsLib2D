#pragma once
#include "GraphicsLib/Math/Rect.h"
#include "GraphicsLib/RawGraphics/RawTexture.h"

#include <filesystem>

namespace gfx2d
{
    using TexturePtr = std::shared_ptr<class Texture>;

    class Texture
    {
    public:
        Texture() = default;
        explicit Texture(const std::filesystem::path& path);

    public:
        static TexturePtr create(const std::filesystem::path& path);

        int getWidth() const { return _width; }
        int getHeight() const { return _height; }
        Rect geTextureRect() const { return _rect; }

        void setSmooth(const bool smooth);
        void setTextureRect(const Rect& rect) {_rect = rect; }

    private:
        void loadTexture(const std::filesystem::path& path);

    private:
        RawTexturePtr _raw{ nullptr };
        Rect _rect;
        int channels{ 0 };
        int _width{};
        int _height{};
        bool _isSmooth{ false };

        friend class Renderer;
        friend class Game;

    };
} // namespace gfx2d