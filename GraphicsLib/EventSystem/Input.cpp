#include "Input.h"

#include "EventDispatcher.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

namespace gfx2d
{
    std::array<bool, 512> Input::_keys{};
    std::array<bool, 8> Input::_mouseButtons{};
    glm::vec2 Input::_mousePos{};

    bool Input::isKeyPressed(const int key) { return _keys[key]; }

    bool Input::isMouseButtonPressed(const int button) { return _mouseButtons[button]; }

    glm::vec2 Input::getMousePosition() { return _mousePos; }

    void Input::onEvent(Event& e)
    {
        EventDispatcher d(e);

        d.dispatch<KeyPressedEvent>(
            [](const KeyPressedEvent& e)
            {
                _keys[e.getKey()] = true;
                return false;
            });

        d.dispatch<KeyReleasedEvent>(
            [](const KeyReleasedEvent& e)
            {
                _keys[e.getKey()] = false;
                return false;
            });

        d.dispatch<MouseMovedEvent>(
            [](const MouseMovedEvent& e)
            {
                _mousePos = { e.getX(), e.getY() };
                return false;
            });

        d.dispatch<MouseButtonPressedEvent>(
            [](const MouseButtonPressedEvent& e)
            {
                _mouseButtons[e.getButton()] = true;
                return false;
            });

        d.dispatch<MouseButtonReleasedEvent>(
            [](const MouseButtonReleasedEvent& e)
            {
                _mouseButtons[e.getButton()] = false;
                return false;
            });
    }

} // namespace gfx2d