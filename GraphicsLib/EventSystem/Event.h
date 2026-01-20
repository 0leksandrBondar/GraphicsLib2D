#pragma once

#define EVENT_CLASS_TYPE(type)                                                                     \
    static EventType getStaticType() { return EventType::type; }                                   \
    EventType getType() const override { return getStaticType(); }                                 \
    const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                                             \
    int getCategoryFlags() const override { return category; }

namespace gfx2d
{
    enum class EventType
    {
        None = 0,

        // Window
        WindowClose,
        WindowResize,

        // Keyboard
        KeyPressed,
        KeyReleased,

        // Mouse
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        Application = 1 << 0,
        Input = 1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 3,
        MouseButton = 1 << 4
    };

    class Event
    {
    public:
        bool handled = false;

        [[nodiscard]] virtual EventType getType() const = 0;
        [[nodiscard]] virtual int getCategoryFlags() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;

        [[nodiscard]] bool isInCategory(EventCategory category) const
        {
            return getCategoryFlags() & category;
        }

        virtual ~Event() = default;
    };
} // namespace gfx2d