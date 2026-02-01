#include "Window.h"

#include "GraphicsLib/EventSystem/KeyEvent.h"
#include "GraphicsLib/EventSystem/MouseEvent.h"
#include "GraphicsLib/OpenGL.h"
#include "GraphicsLib/Tools/Timer.h"

#include <GraphicsLib/EventSystem/Input.h>

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
        : _windowSize({ width, height }),
          _camera{ Camera::create(width, height) },
          _renderer{ Renderer::create(this, _camera.get()) }
    {
        _window = opengl::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        // KEYBOARD
        glfwSetKeyCallback(_window, onKeyboardButton);

        // MOUSE
        glfwSetScrollCallback(_window, onMouseScroll);
        glfwSetCursorPosCallback(_window, onMouseMove);
        glfwSetMouseButtonCallback(_window, onMouseButton);
    }

    void Window::onMouseMove(GLFWwindow* window, const double x, const double y)
    {
        if (!window)
            return;

        MouseMovedEvent e(static_cast<float>(x), static_cast<float>(y));
        Input::onEvent(e);
    }

    void Window::onMouseScroll(GLFWwindow* window, const double x, const double y)
    {
        if (!window)
            return;

        MouseScrolledEvent e(static_cast<float>(x), static_cast<float>(y));
        Input::onEvent(e);
    }

    void Window::onMouseButton(GLFWwindow* window, const int button, const int action, int mods)
    {
        if (!window)
            return;

        if (action == GLFW_PRESS)
        {
            MouseButtonPressedEvent e(button);
            Input::onEvent(e);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseButtonReleasedEvent e(button);
            Input::onEvent(e);
        }
    }

    void Window::onKeyboardButton(GLFWwindow* window, const int key, int scancode, const int action,
                                  int mods)
    {
        if (!window)
            return;

        switch (action)
        {
        case GLFW_PRESS:
        {
            KeyPressedEvent e(key, false);
            Input::onEvent(e);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent e(key);
            Input::onEvent(e);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressedEvent e(key, true);
            Input::onEvent(e);
            break;
        }
        default:;
        }
    }

    WindowPtr Window::create(const unsigned int width, const unsigned int height, const char* title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

} // namespace gfx2d
