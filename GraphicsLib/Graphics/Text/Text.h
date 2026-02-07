#pragma once

#include <GraphicsLib/Graphics/GraphicsItem.h>

namespace gfx2d
{
    class Text final : public GraphicsItem
    {
    public:
        explicit Text(const std::string& text);

    private:
    };

} // namespace gfx2d
