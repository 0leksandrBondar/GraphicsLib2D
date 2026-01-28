#pragma once

#include "GraphicsLib/BaseTypes/Transformable.h"
#include "GraphicsLib/RawGraphics/Mesh.h"
#include "GraphicsLib/RawGraphics/Shader.h"
#include "GraphicsLib/RawGraphics/Texture2D.h"

#include <vector>

namespace gfx2d
{
    class Texture2D;

    class GraphicsItem : public Transformable
    {
    public:
        GraphicsItem() = default;

        void setColor(glm::vec4 color)
        {
            _color = { color.x / 255, color.y / 255, color.z / 255, color.w };
        }
        void setShader(const ShaderPtr& shader) { _shader = shader; }

        [[nodiscard]] glm::vec4 const& getColor() const { return _color; }
        [[nodiscard]] ShaderPtr getShader() const { return _shader; }
        [[nodiscard]] Texture2D const* getTexture() const { return _texture.get(); }
        [[nodiscard]] std::vector<Mesh> const& getMeshes() const { return _meshes; }

    protected:
        ShaderPtr _shader{ nullptr };
        TexturePtr _texture{ nullptr };
        std::vector<Mesh> _meshes;
        glm::vec4 _color{ 255, 255, 255, 1 };
    };
} // namespace gfx2d
