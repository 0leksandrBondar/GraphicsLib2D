#pragma once

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

    private:
        Window(unsigned int width, unsigned int height, const char* title);

    private:
        GLFWwindow* _window{ nullptr };
        OnFrameCallback _onFrameCallback{ nullptr };

        glm::vec2 _windowSize{ 0 };
    };
} // namespace gfx2d