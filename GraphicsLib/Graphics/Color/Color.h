#pragma once

namespace gfx2d
{

    enum class DefColor
    {
        White,
        Black,
        Red,
        Green,
        Blue,
        Yellow,
        Cyan,
        Magenta,
        Gray,
        LightGray,
        DarkGray,
        Orange,
        Purple,
        Pink,
        Brown
    };

    struct ColorData
    {
        int red{ 0 };
        int green{ 0 };
        int blue{ 0 };
        int alpha{ 1 };
    };

    class Color final
    {
    public:
        Color() = default;
        Color(const int red, const int green, const int blue, const int alpha)
        {
            _data = { red, green, blue, alpha };
        }

        void setRGBColor(const int red, const int green, const int blue, const int alpha)
        {
            _data.red = red;
            _data.green = green;
            _data.blue = blue;
            _data.alpha = alpha;
        }

        explicit Color(const DefColor definedColor)
        {
            // clang-format off
            switch (definedColor)
            {
            case DefColor::Black:     _data = {0,0,0,255}; break;
            case DefColor::Red:       _data = {255,0,0,255}; break;
            case DefColor::Green:     _data = {0,255,0,255}; break;
            case DefColor::Blue:      _data = {0,0,255,255}; break;
            case DefColor::DarkGray:  _data = {64,64,64,255}; break;
            case DefColor::Purple:    _data = {128,0,128,255}; break;
            case DefColor::Brown:     _data = {139,69,19,255}; break;
            case DefColor::Orange:    _data = {255,165,0,255}; break;
            case DefColor::Yellow:    _data = {255,255,0,255}; break;
            case DefColor::Cyan:      _data = {0,255,255,255}; break;
            case DefColor::Magenta:   _data = {255,0,255,255}; break;
            case DefColor::White:     _data = {255,255,255,255}; break;
            case DefColor::Gray:      _data = {128,128,128,255}; break;
            case DefColor::LightGray: _data = {192,192,192,255}; break;
            case DefColor::Pink:      _data = {255,192,203,255}; break;
            }
            //clang-format on
        }
        [[nodiscard]] float r() const { return _data.red / 255.0f; }
        [[nodiscard]] float g() const { return _data.green / 255.0f; }
        [[nodiscard]] float b() const { return _data.blue / 255.0f; }
        [[nodiscard]] float a() const { return _data.alpha; }

    private:
        ColorData _data;
    };
} // namespace gfx2d