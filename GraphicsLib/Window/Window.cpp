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
        : _windowSize({ width, height })
    {
        _window = opengl::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        // KEYBOARD
        glfwSetKeyCallback(_window, onKeyboardButton);

        // MOUSE
        glfwSetScrollCallback(_window, onMouseScroll);
        glfwSetCursorPosCallback(_window, onMouseMove);
        glfwSetMouseButtonCallback(_window, onMouseButton);
    }

    void Window::onMouseMove(GLFWwindow* window, double x, double y)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (!window)
            return;

        MouseMovedEvent e((float)x, (float)y);
        self->dispatchEvent(e);
    }

    void Window::onMouseScroll(GLFWwindow* window, double x, double y)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (!window)
            return;

        MouseScrolledEvent e(static_cast<float>(x), static_cast<float>(y));
        self->dispatchEvent(e);
    }

    void Window::onMouseButton(GLFWwindow* window, int button, int action, int mods)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (!window)
            return;

        if (action == GLFW_PRESS)
        {
            MouseButtonPressedEvent e(button);
            self->dispatchEvent(e);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseButtonReleasedEvent e(button);
            self->dispatchEvent(e);
        }
    }

    void Window::onKeyboardButton(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!window)
            return;

        switch (action)
        {
        case GLFW_PRESS:
        {
            KeyPressedEvent e(key, false);
            self->dispatchEvent(e);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent e(key);
            self->dispatchEvent(e);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressedEvent e(key, true);
            self->dispatchEvent(e);
            break;
        }
        default:;
        }
    }

    void Window::dispatchEvent(Event& e) const { Input::onEvent(e); }

    WindowPtr Window::create(const unsigned int width, const unsigned int height, const char* title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

} // namespace gfx2d
