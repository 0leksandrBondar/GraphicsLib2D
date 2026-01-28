
#pragma once

#include "NonCopyableButMovable.h"

#include <memory>

namespace gfx2d
{
    template <class T>
    class Singleton : public NonCopyableButMovable
    {
    public:
        static T* getInstance()
        {
            static std::unique_ptr<T> instance;
            if (instance == nullptr)
            {
                instance = std::unique_ptr<T>(new T);
            }
            return instance.get();
        }
    };
} // namespace BondEngine