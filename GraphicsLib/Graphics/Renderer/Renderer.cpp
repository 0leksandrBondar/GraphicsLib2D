#include "Renderer.h"

#include "GraphicsLib/Camera/Camera.h"
#include "GraphicsLib/Graphics/GraphicsItem.h"
#include "GraphicsLib/RawGraphics/Texture2D.h"
#include "glm/ext/matrix_clip_space.hpp"

#include <iostream>

#define GL_CHECK()                                                                                 \
    while (GLenum err = glGetError())                                                              \
        std::cout << "OpenGL error: " << err << std::endl;

namespace gfx2d
{

    Renderer::Renderer(Window* window, Camera* camera) : _window(window), _camera(camera)
    {
        _projectionMatrix
            = glm::ortho(0.f, _window->getSize().x, _window->getSize().y, 0.f, -100.f, 100.f);
    }

    RendererPtr Renderer::create(Window* window, Camera* camera)
    {
        return std::make_unique<Renderer>(window, camera);
    }

    void Renderer::render(GraphicsItem* item) const
    {
        updateMatrices(item);
        // color not implemented yet
        // item->getShader()->setVector4("color", item->getColor());

        const auto hasTexture = item->getTexture() != nullptr;

        item->getShader()->setBool("useTexture", hasTexture);

        if (hasTexture)
            item->getTexture()->bind();

        for (auto& mesh : item->getMeshes())
        {
            mesh.bindVertexArrayObject();
            glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
            GL_CHECK();
        }

        if (hasTexture)
            item->getTexture()->unbind();
    }

    void Renderer::updateMatrices(GraphicsItem* item) const
    {
        if (item->getShader() != nullptr)
        {
            item->getShader()->use();
            item->getShader()->setMatrix4("modelMat", item->getTransformMatrix());
            item->getShader()->setMatrix4("projectionMat", _projectionMatrix);

            if (_camera != nullptr)
                item->getShader()->setMatrix4("viewMat", _camera->getViewMatrix());
            else
                item->getShader()->setMatrix4("viewMat", glm::mat4(1.0f));
        }
    }

} // namespace gfx2d
