#include "Renderer.h"

#include "GraphicsLib/Camera/Camera.h"
#include "GraphicsLib/Graphics/GraphicsItem.h"
#include "GraphicsLib/RawGraphics/Texture.h"
#include "GraphicsLib/Resource/ResourceManager.h"
#include "GraphicsLib/Window/Window.h"
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

    void Renderer::render(GraphicsItem* item)
    {
        if (item->getShader() == nullptr)
            _shader = ResourceManager::getInstance()->getShader("defaultShader");
        else
            _shader = item->getShader();

        updateMatrices(item);
        _shader->setVector4("spriteColor", item->getColor());

        const auto hasTexture = item->getTexture() != nullptr;

        _shader->setBool("useTexture", hasTexture);

        if (hasTexture)
            item->getTexture()->bind();

        for (auto& mesh : item->getMeshes())
        {
            mesh.bindVertexArrayObject();
            glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
        }

        if (hasTexture)
            item->getTexture()->unbind();
    }

    void Renderer::updateMatrices(GraphicsItem* item) const
    {
        if (_shader != nullptr)
        {
            _shader->use();
            _shader->setMatrix4("modelMat", item->getTransformMatrix());
            _shader->setMatrix4("projectionMat", _projectionMatrix);

            if (_camera != nullptr)
                _shader->setMatrix4("viewMat", _camera->getViewMatrix());
            else
                _shader->setMatrix4("viewMat", glm::mat4(1.0f));
        }
    }

} // namespace gfx2d
