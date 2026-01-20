#include "Window.h"

#include "GraphicsLib/EventSystem/KeyEvent.h"
#include "GraphicsLib/EventSystem/MouseEvent.h"
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

        // ===============================
        // KEYBOARD
        // ===============================
        glfwSetKeyCallback(_window,
                           [](GLFWwindow* win, int key, int, int action, int)
                           {
                               auto* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
                               if (!window || !window->_onEventCallback)
                                   return;

                               switch (action)
                               {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent e(key, false);
                                   window->_onEventCallback(e);
                                   break;
                               }
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent e(key);
                                   window->_onEventCallback(e);
                                   break;
                               }
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent e(key, true);
                                   window->_onEventCallback(e);
                                   break;
                               }
                               default:;
                               }
                           });

        // ===============================
        // MOUSE MOVE
        // ===============================
        glfwSetCursorPosCallback(_window,
                                 [](GLFWwindow* win, double x, double y)
                                 {
                                     auto* window
                                         = static_cast<Window*>(glfwGetWindowUserPointer(win));
                                     if (!window || !window->_onEventCallback)
                                         return;

                                     MouseMovedEvent e((float)x, (float)y);
                                     window->_onEventCallback(e);
                                 });

        // ===============================
        // MOUSE BUTTON
        // ===============================
        glfwSetMouseButtonCallback(_window,
                                   [](GLFWwindow* win, int button, int action, int)
                                   {
                                       auto* window
                                           = static_cast<Window*>(glfwGetWindowUserPointer(win));
                                       if (!window || !window->_onEventCallback)
                                           return;

                                       if (action == GLFW_PRESS)
                                       {
                                           MouseButtonPressedEvent e(button);
                                           window->_onEventCallback(e);
                                       }
                                       else if (action == GLFW_RELEASE)
                                       {
                                           MouseButtonReleasedEvent e(button);
                                           window->_onEventCallback(e);
                                       }
                                   });

        // ===============================
        // SCROLL
        // ===============================
        // glfwSetScrollCallback(_window,
        //                       [](GLFWwindow* win, double xoff, double yoff)
        //                       {
        //                           auto* window
        //                               = static_cast<Window*>(glfwGetWindowUserPointer(win));
        //                           if (!window || !window->_onEventCallback)
        //                               return;
        //
        //                           MouseScrolledEvent e((float)xoff, (float)yoff);
        //                           window->_onEventCallback(e);
        //                       });
    }

    WindowPtr Window::create(const unsigned int width, const unsigned int height, const char* title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

} // namespace gfx2d