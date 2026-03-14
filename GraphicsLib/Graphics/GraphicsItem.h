#pragma once

#include "Color/Color.h"
#include "GraphicsLib/BaseTypes/Transformable.h"
#include "GraphicsLib/Graphics/Texture/Texture.h"
#include "GraphicsLib/Math/Rect.h"
#include "GraphicsLib/RawGraphics/Mesh.h"
#include "GraphicsLib/RawGraphics/Shader.h"

#include <vector>

namespace gfx2d
{
    class Texture;

    class GraphicsItem : public Transformable
    {
    public:
        GraphicsItem() = default;

        void setColor(const int R, const int G, const int B, const int A = 1.f)
        {
            _color = { R, G, B, A };
        }

        void setColor(const DefColor color) { _color = Color(color); }

        void setShader(const ShaderPtr& shader) { _shader = shader; }

        void setTexture(const TexturePtr& texture) { _texture = texture; }
        void setTextureRect(const Rect textureRect) {}

        [[nodiscard]] Color getColor() const { return _color; }
        [[nodiscard]] glm::vec4 getColorVec4() const
        {
            return { _color.r(), _color.g(), _color.b(), _color.a() };
        }
        [[nodiscard]] ShaderPtr getShader() const { return _shader; }
        [[nodiscard]] TexturePtr getTexture() const { return _texture; }
        [[nodiscard]] std::vector<Mesh> const& getMeshes() const { return _meshes; }

    protected:
        ShaderPtr _shader{ nullptr };
        TexturePtr _texture{ nullptr };
        std::vector<Mesh> _meshes;
        Color _color{ 255, 255, 255, 1 };
    };
} // namespace gfx2d
