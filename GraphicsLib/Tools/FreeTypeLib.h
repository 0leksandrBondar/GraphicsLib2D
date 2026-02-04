#pragma once

#include "GraphicsLib/BaseTypes/Singleton.h"
#include "freetype/freetype.h"

namespace gfx2d
{
    class FreeTypeLibrary final : public Singleton<FreeTypeLibrary>
    {
    public:
        ~FreeTypeLibrary();
        void initFreeTypeLibrary();
        void destroyFreeTypeLibrary() const;

        FT_Library& getFreeTypeLib() { return _library; }

    private:
        FT_Library _library{ nullptr };
    };
} // namespace gfx2d