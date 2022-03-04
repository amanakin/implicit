#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <cstdint>

#include <vector4.h>

// Color - RGBA
struct Color: public Vector4f {
    Color() noexcept;

    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) noexcept :
            Vector4f(static_cast<float>(r) / 255.f,
                     static_cast<float>(g) / 255.f,
                     static_cast<float>(b) / 255.f,
                     static_cast<float>(a) / 255.f)
    {}

    explicit Color(const char* hexRGB) noexcept; // "7FFF00", etc., apacity by default 255
    explicit Color(uint32_t color) noexcept;     // RGBA, little endian

    uint32_t toInteger() const; // RGBA, little endian

    std::string toHex() const; // RGB: "7FFF00"
};

namespace Colors {
constexpr Color RED    = Color(255, 0,   0);
constexpr Color GREEN  = Color(0,   128, 0);
constexpr Color BLUE   = Color(0,   0,   255);
constexpr Color YELLOW = Color(255, 244, 32);

constexpr Color BLACK = Color(  0,   0,   0);
constexpr Color WHITE = Color(255, 255, 255);

constexpr Color LIGHT_GREY = Color(220, 220, 220);
constexpr Color GREY       = Color(128, 128, 128);
constexpr Color DARK_GREY  = Color( 64,  64,  64);

constexpr Color LIGHT_BLUE = Color(173, 216, 230);
constexpr Color AQUA       = Color(  0, 255, 255);
constexpr Color SKY_BLUE   = Color(  0, 191, 255);

constexpr Color LIGHT_RED = Color(240, 128, 128);
constexpr Color ORANGE    = Color(255, 160,  16);
constexpr Color CRIMSON   = Color(220,  20,  60);

constexpr Color LIGHT_GREEN = Color(144, 238, 144);
constexpr Color LIME        = Color(0,   255,   0);
constexpr Color SEA_GREEN   = Color(32,  178, 170);

constexpr Color BROWN = Color(165, 42, 42);

}

// Hue: [0, 360], sat: [0, 100], val: [0, 100], opacity: [0, 1]
struct ColorHSVA: public Vector4f {
    ColorHSVA(float hue, float saturation, float value, float opacity = 1) noexcept;
};

Color     ConvertHSVAToRGBA(const ColorHSVA& hsva);
ColorHSVA ConvertRGBAToHSVA(const Color& rgba);

//*************************************************************

#endif // COLOR_HEADER
