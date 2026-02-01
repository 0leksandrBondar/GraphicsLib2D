#pragma once

#include "GraphicsLib/Camera/Camera.h"
#include "GraphicsLib/EventSystem/Event.h"
#include "GraphicsLib/EventSystem/Input.h"
#include "GraphicsLib/Graphics/Renderer/Renderer.h"
#include "GraphicsLib/OpenGL.h"
#include "glm/vec2.hpp"

namespace gfx2d
{
    using WindowPtr = std::unique_ptr<class Window>;
    using OnFrameCallback = std::function<void(float deltaTime)>;

    class Window final
    {
    public:
        static WindowPtr create(unsigned int width, unsigned int height, const char* title);
        ~Window();

        void runMainLoop() const;

        void setOnFrameCallback(const OnFrameCallback& callback) { _onFrameCallback = callback; }

        [[nodiscard]] glm::vec2 getSize() const { return _windowSize; }
        CameraPtr& getCamera() { return _camera; }
        RendererPtr& getRenderer() { return _renderer; }

    private:
        Window(unsigned int width, unsigned int height, const char* title);

        static void onMouseMove(GLFWwindow* window, double x, double y);
        static void onMouseScroll(GLFWwindow* window, double x, double y);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onKeyboardButton(GLFWwindow* window, int key, int scancode, int action,
                                     int mods);

    private:
        GLFWwindow* _window{ nullptr };
        OnFrameCallback _onFrameCallback{ nullptr };

        glm::vec2 _windowSize{ 0 };

        CameraPtr _camera{ nullptr };
        RendererPtr _renderer{ nullptr };
    };
} // namespace gfx2d
