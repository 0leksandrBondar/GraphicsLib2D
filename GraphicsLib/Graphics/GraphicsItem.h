#pragma once

#include "GraphicsLib/BaseTypes/Transformable.h"
#include "GraphicsLib/RawGraphics/Mesh.h"
#include "GraphicsLib/RawGraphics/Shader.h"

#include <vector>

namespace gfx2d
{
    class Texture2D;

    class GraphicsItem : public Transformable
    {
    public:
        GraphicsItem() = default;
        [[nodiscard]] Shader const* getShader() const { return _shader; }
        [[nodiscard]] Texture2D const* getTexture() const { return _texture; }
        [[nodiscard]] std::vector<Mesh> const& getMeshes() const { return _meshes; }

    protected:
        Shader* _shader{ nullptr };
        Texture2D* _texture{ nullptr };
        std::vector<Mesh> _meshes;
    };
} // namespace gfx2d
