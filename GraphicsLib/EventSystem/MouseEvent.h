#pragma once
#include "Event.h"

namespace gfx2d
{
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y) : _x(x), _y(y) {}

        [[nodiscard]] float getX() const { return _x; }
        [[nodiscard]] float getY() const { return _y; }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(Input | Mouse)

    private:
        float _x, _y;
    };

    class MouseButtonEvent : public Event
    {
    public:
        [[nodiscard]] int getButton() const { return _button; }

        [[nodiscard]] int getCategoryFlags() const override
        {
            return EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton;
        }

    protected:
        explicit MouseButtonEvent(const int button) : _button(button) {}
        int _button;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
        EVENT_CLASS_CATEGORY(Input | Mouse | MouseButton)
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
        EVENT_CLASS_CATEGORY(Input | Mouse | MouseButton)
    };

} // namespace gfx2d
