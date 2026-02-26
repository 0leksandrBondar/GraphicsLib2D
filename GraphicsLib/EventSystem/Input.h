#pragma once

#include "GraphicsLib/EventSystem/ButtonDefinisions.h"

#include "glm/vec2.hpp"

#include <array>

namespace gfx2d
{
    class Event;

    class Input
    {
    public:
        static void onEvent(Event& e);

        static bool isKeyPressed(int key);
        static bool isMouseButtonPressed(int button);
        static glm::vec2 getMousePosition();
        // static glm::vec2 getMouseScroll();
        static glm::vec2 consumeMouseScroll();

        static bool isKeyJustPressed(int key);
        static bool isMouseButtonJustPressed(const int button);


        static void update();

    private:
        static std::array<bool, 512> _keys;
        static std::array<bool, 512> _prevKeys;
        static std::array<bool, 8> _mouseButtons;
        static std::array<bool, 8> _prevMouseButtons;
        static glm::vec2 _mousePos;
        static glm::vec2 _mouseScroll;
    };
} // namespace gfx2d
