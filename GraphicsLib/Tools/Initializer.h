#pragma once

#include "FreeTypeLib.h"
#include "GraphicsLib/OpenGL.h"

namespace gfx2d::initializer
{
    inline void initializeGL()
    {
        if (!glfwInit())
            spdlog::error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        FreeTypeLibrary::getInstance()->initFreeTypeLibrary();
    }
} // namespace gfx2d::initializer
