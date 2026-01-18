#include "Window.h"

#include "GraphicsLib/OpenGL.h"
#include "GraphicsLib/Tools/Timer.h"

namespace gfx2d
{

    Window::~Window() { glfwTerminate(); }

    void Window::runMainLoop() const
    {
        Timer timer;
        while (!glfwWindowShouldClose(_window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            timer.update();
            const auto deltaTime = timer.getDeltaTime();

            if (_onFrameCallback)
                _onFrameCallback(deltaTime);

            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }

    Window::Window(const unsigned int width, const unsigned int height, const char* title)
        : _windowSize({ width, height })
    {
        _window = opengl::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);
    }

    WindowPtr Window::create(const unsigned int width, const unsigned int height, const char* title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

} // namespace gfx2d