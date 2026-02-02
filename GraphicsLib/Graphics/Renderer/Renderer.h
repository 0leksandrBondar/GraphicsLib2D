#pragma once

#include "GraphicsLib/Camera/Camera.h"
#include "GraphicsLib/RawGraphics/Shader.h"

namespace gfx2d
{
    class Camera;
    class GraphicsItem;

    using RendererPtr = std::unique_ptr<class Renderer>;

    class Renderer final
    {
    public:
        Renderer() = default;
        static RendererPtr create(const CameraPtr& camera = nullptr);
        explicit Renderer(CameraPtr  camera);

        void render(GraphicsItem* item);

    private:
        void updateMatrices(GraphicsItem* item) const;

    private:
        CameraPtr _camera{ nullptr };
        ShaderPtr _shader{ nullptr };
    };
} // namespace gfx2d
