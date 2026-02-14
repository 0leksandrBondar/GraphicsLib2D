file(
        GLOB Sources
        "*.h"
        "*.cpp"
        "Tools/*.h"
        "Tools/*.cpp"
        "Window/*.h"
        "Window/*.cpp"
        "Camera/*.h"
        "Camera/*.cpp"
        "BaseTypes/*.h"
        "BaseTypes/*.cpp"
        "RawGraphics/*.h"
        "RawGraphics/*.cpp"
        "EventSystem/*.h"
        "EventSystem/*.cpp"
        "Graphics/*.h"
        "Graphics/*.cpp"
        "Graphics/Color/*.h"
        "Graphics/Color/*.cpp"
        "Graphics/Sprite/*.h"
        "Graphics/Sprite/*.cpp"
        "Graphics/Renderer/*.cpp"
        "Graphics/Renderer/*.cpp"
        "Graphics/Animation/*.h"
        "Graphics/Animation/*.cpp"
        "Graphics/Text/*.h"
        "Graphics/Text/*.cpp"
        "Resource/*.h"
        "Resource/*.cpp"
)

add_library(
        GraphicsLib STATIC
        ${Sources})

target_include_directories(
        GraphicsLib PUBLIC
        ../)

target_link_libraries(
        GraphicsLib PUBLIC
        glad
        glm
        glfw
        freetype
        spdlog::spdlog
)
