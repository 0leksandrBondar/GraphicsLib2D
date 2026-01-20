#pragma once
#include "Event.h"

namespace gfx2d
{
    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& event) : _event(event) {}

        template<typename T, typename F>
        bool dispatch(const F& func)
        {
            if (_event.getType() == T::getStaticType())
            {
                _event.handled |= func(static_cast<T&>(_event));
                return true;
            }
            return false;
        }

    private:
        Event& _event;
    };
}
