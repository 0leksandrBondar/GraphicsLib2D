#include "Renderer.h"

#include "GraphicsLib/Camera/Camera.h"
#include "GraphicsLib/Graphics/GraphicsItem.h"
#include "GraphicsLib/RawGraphics/Texture.h"
#include "GraphicsLib/Resource/ResourceManager.h"
#include "GraphicsLib/Window/Window.h"
#include "glm/ext/matrix_clip_space.hpp"

#include <iostream>
#include <utility>

#define GL_CHECK()                                                                                 \
    while (GLenum err = glGetError())                                                              \
        std::cout << "OpenGL error: " << err << std::endl;

namespace gfx2d
{

    Renderer::Renderer(CameraPtr camera) : _camera(std::move(camera)) {}

    RendererPtr Renderer::create(const CameraPtr& camera)
    {
        return std::make_unique<Renderer>(camera);
    }

    void Renderer::render(GraphicsItem* item)
    {
        if (item->getShader() == nullptr)
            throw std::runtime_error(
                "Renderer::render(GraphicsItem* item) item has invalid shader");

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
            Texture::unbind();
    }

    void Renderer::updateMatrices(GraphicsItem* item) const
    {
        if (_shader != nullptr)
        {
            _shader->use();
            _shader->setMatrix4("modelMat", item->getTransformMatrix());

            if (_camera != nullptr)
            {
                _shader->setMatrix4("projectionMat", _camera->getProjectionMatrix());
                _shader->setMatrix4("viewMat", _camera->getViewMatrix());
            }
            else
            {
                _shader->setMatrix4("projectionMat", glm::mat4(1.0f));
                _shader->setMatrix4("viewMat", glm::mat4(1.0f));
            }
        }
    }

} // namespace gfx2d
