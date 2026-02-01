#pragma once

#include "GraphicsLib/BaseTypes/Transformable.h"
#include "GraphicsLib/RawGraphics/Mesh.h"
#include "GraphicsLib/RawGraphics/Shader.h"
#include "GraphicsLib/RawGraphics/Texture.h"

#include <vector>

namespace gfx2d
{
    class Texture;

    class GraphicsItem : public Transformable
    {
    public:
        GraphicsItem() = default;

        void setColor(const int R, const int G, const int B)
        {
            constexpr float alpha = 1.0f;
            _color = { R / 255.f, G / 255.f, B / 255.f, alpha };
        }

        void setShader(const ShaderPtr& shader) { _shader = shader; }
        void setTexture(const TexturePtr& texture) { _texture = texture; }

        glm::vec4 getColor() const
        {
            if (_texture)
                return glm::vec4(1.f);
            return _color;
        }
        [[nodiscard]] ShaderPtr getShader() const { return _shader; }
        [[nodiscard]] Texture const* getTexture() const { return _texture.get(); }
        [[nodiscard]] std::vector<Mesh> const& getMeshes() const { return _meshes; }

    protected:
        ShaderPtr _shader{ nullptr };
        TexturePtr _texture{ nullptr };
        std::vector<Mesh> _meshes;
        glm::vec4 _color{ 255, 255, 255, 1 };
    };
} // namespace gfx2d
