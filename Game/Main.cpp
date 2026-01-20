#include "GraphicsLib/EventSystem/ButtonDefinisions.h"
#include "GraphicsLib/EventSystem/Input.h"
#include "GraphicsLib/Graphics/Renderer/Renderer.h"
#include "GraphicsLib/Graphics/Sprite/Sprite.h"
#include "GraphicsLib/RawGraphics/Shader.h"
#include "GraphicsLib/RawGraphics/Texture2D.h"
#include "GraphicsLib/Tools/Initializer.h"
#include "GraphicsLib/Window/Window.h"

class Game
{
public:
    Game()
    {
        initializeAllMembers();
        initEventSystem();
        _window->setOnFrameCallback([this](const float deltaTime) { onFrame(deltaTime); });
    }

    void run() const { _window->runMainLoop(); }

    void initEventSystem() const
    {
        _window->setOnEventCallback([](gfx2d::Event& e) { gfx2d::Input::onEvent(e); });
    }

    void initializeAllMembers()
    {
        const auto vertShaderPath = "Assets/Shaders/Vertex.vert";
        const auto fragShaderPath = "Assets/Shaders/Fragment.frag";
        const auto texturePath = "Assets/Textures/DefaultTexture.png";

        _window = gfx2d::Window::create(1000, 800, "gfx2d");
        _shader = gfx2d::Shader::create(vertShaderPath, fragShaderPath);
        _sprite = gfx2d::Sprite::create(_shader.get(), texturePath);
        _sprite->setPosition({ 350, 270 });
        _sprite->setSize(200, 200);
        _renderer = gfx2d::Renderer::create(_window.get());
    }

private:
    void onFrame(const float deltaTime) const
    {
        if (gfx2d::Input::isMouseButtonPressed(gfx2d::Mouse::LeftButton))
            spdlog::info("Left button down");
        if (gfx2d::Input::isMouseButtonPressed(gfx2d::Mouse::RightButton))
            spdlog::info("Right button down");

        constexpr int speed = 350;

        if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::W))
            _sprite->move(0, -speed * deltaTime);
        if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::A))
            _sprite->move(-speed * deltaTime, 0);
        if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::S))
            _sprite->move(0, speed * deltaTime);
        if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::D))
            _sprite->move(speed * deltaTime, 0);

        _renderer->render(_sprite.get());
    }

    gfx2d::WindowPtr _window{ nullptr };
    gfx2d::ShaderPtr _shader{ nullptr };
    gfx2d::SpritePtr _sprite{ nullptr };
    gfx2d::RendererPtr _renderer{ nullptr };
};

int main()
{
    gfx2d::initializer::initializeGL();

    const Game game;
    game.run();

    return 0;
}