#pragma once

#include "GraphicsLib/Window/Window.h"
#include "glm/mat4x4.hpp"

namespace gfx2d
{
    class GraphicsItem;

    using RendererPtr = std::unique_ptr<class Renderer>;

    class Renderer final
    {
        Renderer() = default;
        explicit Renderer(Window* window);

    public:
        static RendererPtr create(Window* window);

        void render(GraphicsItem* item) const;

    private:
        void updateMatrices(GraphicsItem* item) const;

    private:
        Window* _window{ nullptr };
        glm::mat4 _projectionMatrix{ 1.f };
    };
} // namespace gfx2d