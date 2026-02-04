#include "FreeTypeLib.h"

#include <iostream>

namespace gfx2d
{
    FreeTypeLibrary::~FreeTypeLibrary() { destroyFreeTypeLibrary(); }

    void FreeTypeLibrary::initFreeTypeLibrary()
    {
        if (const FT_Error error = FT_Init_FreeType(&_library); error != FT_Err_Ok)
        {
            std::cerr << "Failed to initialize FreeType library. Error code: " << error
                      << std::endl;
            return;
        }
    }

    void FreeTypeLibrary::destroyFreeTypeLibrary() const { FT_Done_FreeType(_library); }
} // namespace gfx2d