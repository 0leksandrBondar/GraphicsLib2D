#pragma once

#include "GraphicsLib/Window/Window.h"
#include "glm/mat4x4.hpp"

namespace gfx2d
{
    class Camera;
    class GraphicsItem;

    using RendererPtr = std::unique_ptr<class Renderer>;

    class Renderer final
    {
    public:
        Renderer() = default;
        static RendererPtr create(Window* window, Camera* camera = nullptr);
        explicit Renderer(Window* window, Camera* camera);

        void render(GraphicsItem* item) const;

    private:
        void updateMatrices(GraphicsItem* item) const;

    private:
        Window* _window{ nullptr };
        Camera* _camera{ nullptr };
        glm::mat4 _projectionMatrix{ 1.f };
    };
} // namespace gfx2d