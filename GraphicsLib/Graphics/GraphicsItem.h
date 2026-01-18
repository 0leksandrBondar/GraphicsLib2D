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
        [[nodiscard]] Shader const* getShader() const { return _shader; }
        [[nodiscard]] Texture2D const* getTexture() const { return _texture.get(); }
        [[nodiscard]] std::vector<Mesh> const& getMeshes() const { return _meshes; }

    protected:
        Shader* _shader{ nullptr };
        TexturePtr _texture{ nullptr };
        std::vector<Mesh> _meshes;
    };
} // namespace gfx2d
