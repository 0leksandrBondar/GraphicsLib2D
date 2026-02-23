#include "GraphicsLib/Graphics/Sprite/Sprite.h"
#include "GraphicsLib/RawGraphics/UniformBufferObject.h"
#include "GraphicsLib/Tools/Initializer.h"
#include "GraphicsLib/Window/Window.h"
#include "ResourceManager/ResourceManager.h"

struct CameraData
{
    alignas(16) glm::mat4 view{ 1.f };
    alignas(16) glm::mat4 projection{ 1.f };
};

void updateCameraUBO(const gfx2d::CameraPtr& camera, gfx2d::UniformBufferObject& ubo)
{
    CameraData camData{};
    camData.view = camera->getViewMatrix();
    camData.projection = camera->getProjectionMatrix();

    ubo.updateData(&camData, sizeof(CameraData));
}

void update(const float deltaTime, const gfx2d::CameraPtr& camera)
{
    int speed = 300;
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::LShift))
        speed *= 2;
    else
        speed = 300;

    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::W))
        camera->move({ 0, -speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::A))
        camera->move({ -speed * deltaTime, 0 });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::S))
        camera->move({ 0, speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::D))
        camera->move({ speed * deltaTime, 0 });
}

void render(gfx2d::GraphicsItem* item, const gfx2d::CameraPtr& camera)
{
    item->getShader()->use();
    item->getShader()->setMatrix4("modelMat", item->getTransformMatrix());
 
    item->getShader()->setBool("useTexture", item->getTexture() != nullptr);
    const glm::vec4 color = { item->getColor().r(), item->getColor().g(), item->getColor().b(),
                              item->getColor().a() };

    item->getShader()->setVector4("spriteColor", color);

    if (item->getTexture() != nullptr)
        item->getTexture()->bind();

    for (auto& mesh : item->getMeshes())
    {
        mesh.bindVertexArrayObject();
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    }

    gfx2d::Texture::unbind();
}

using namespace gfx2d;

int main()
{
    initializer::initializeGL();

    const auto window = Window::create(1100, 800, "Example");
    ResourceManager::getInstance()->loadAllResources();
    const auto sprite = Sprite::create(ResourceManager::getInstance()->getShader("defaultShader"));

    sprite->setTexture(ResourceManager::getInstance()->getTexture("Player_idle"));
    sprite->setSize(300, 300);

    UniformBufferObject cameraUBO;
    cameraUBO.create(sizeof(CameraData), 0);

    window->setOnFrameCallback(
        [&](const float deltaTime)
        {
            update(deltaTime, window->getCamera());
            updateCameraUBO(window->getCamera(), cameraUBO);
            render(sprite.get(), window->getCamera());
        });

    window->runMainLoop();
    return 0;
}
