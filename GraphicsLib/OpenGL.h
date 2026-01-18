#pragma once

#include "spdlog/spdlog.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//clang-format on

namespace gfx2d::opengl
{
    inline int initGLAD() { return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); }

    inline  GLFWwindow* createWindow(const unsigned int width, const unsigned int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            spdlog::error("Failed to create GLFW window");
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        initGLAD();
        return window;
    }

}