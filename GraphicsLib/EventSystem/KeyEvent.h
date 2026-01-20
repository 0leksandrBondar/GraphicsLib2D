#pragma once
#include "Event.h"

namespace gfx2d
{
    class KeyEvent : public Event
    {
    public:
        [[nodiscard]] int getKey() const { return _key; }

        [[nodiscard]] int getCategoryFlags() const override
        {
            return EventCategory::Input | EventCategory::Keyboard;
        }

    protected:
        explicit KeyEvent(const int key) : _key(key) {}
        int _key;
    };

    class KeyPressedEvent final : public KeyEvent
    {
    public:
        KeyPressedEvent(const int key, const bool repeat) : KeyEvent(key), _repeat(repeat) {}

        [[nodiscard]] bool isRepeat() const { return _repeat; }

        EVENT_CLASS_TYPE(KeyPressed)
        EVENT_CLASS_CATEGORY(Input | Keyboard)

    private:
        bool _repeat;
    };

    class KeyReleasedEvent final : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const int key) : KeyEvent(key) {}

        EVENT_CLASS_TYPE(KeyReleased)
        EVENT_CLASS_CATEGORY(Input | Keyboard)
    };

} // namespace gfx2d
