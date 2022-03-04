// color.cc

#include <algorithm>
#include <cassert>

#include <utils.h>
#include <color.h>

Color::Color() noexcept :
    Vector4f(0, 0, 0, 1)
{}

Color::Color(const char* hexRGB) noexcept {
    assert(hexRGB != nullptr);

    x = static_cast<float>(HexToDec(hexRGB[0]) * 16 + HexToDec(hexRGB[1]));
    y = static_cast<float>(HexToDec(hexRGB[2]) * 16 + HexToDec(hexRGB[3]));
    z = static_cast<float>(HexToDec(hexRGB[4]) * 16 + HexToDec(hexRGB[5]));
    t = 1;
}

Color::Color(uint32_t color) noexcept {
    auto colorArray = (const unsigned char*)&color;

    x = static_cast<float>(colorArray[0]) / 255;
    y = static_cast<float>(colorArray[1]) / 255;
    z = static_cast<float>(colorArray[2]) / 255;
    t = static_cast<float>(colorArray[3]) / 255;
}

uint32_t Color::toInteger() const {
    return (static_cast<uint32_t>(t * 255) << 24) +
           (static_cast<uint32_t>(z * 255) << 16) +
           (static_cast<uint32_t>(y * 255) << 8)  +
            static_cast<uint32_t>(x * 255);
}

#include <iostream>

std::string Color::toHex() const {
    std::string str;
    str += StringFormat("%02X", static_cast<int>(x * 255));
    str += StringFormat("%02X", static_cast<int>(y * 255));
    str += StringFormat("%02X", static_cast<int>(z * 255));

    return str;
}

//*************************************************************

ColorHSVA::ColorHSVA(float hue, float saturation, float value, float opacity) noexcept :
    Vector4f(hue, saturation, value, opacity)
{}

Color ConvertHSVAToRGBA(const ColorHSVA& hsva) {
    int hueBy60 = (int(hsva.x) / 60) % 6;

    float val = hsva.z;
    float valMin = val * (100 - hsva.y) / 100;
    float a = (val - valMin) * (float(int(hsva.x) % 60) / 60);
    float valInc = valMin + a;
    float valDec = val - a;

    Vector4f percents;

    switch(hueBy60) {
        case 0: 
            percents =  Vector4f(val,    valInc, valMin);
            break;
        case 1: 
            percents =  Vector4f(valDec, val,    valMin);
            break;
        case 2: 
            percents =  Vector4f(valMin, val,    valInc);
            break;
        case 3: 
            percents =  Vector4f(valMin, valDec, val);
            break;
        case 4: 
            percents =  Vector4f(valInc, valMin, val);
            break;
        case 5: 
            percents =  Vector4f(val,    valMin, valDec);
            break;
        default:
            assert("impossible convert in ConvertHSVAToRGBA");
            break;
    };

    return {static_cast<unsigned char>(percents.x * 255 / 100),
            static_cast<unsigned char>(percents.y * 255 / 100),
            static_cast<unsigned char>(percents.z * 255 / 100),
            static_cast<unsigned char>(hsva.t * 255)};
}

ColorHSVA ConvertRGBAToHSVA(const Color& rgba) {
    float max = std::max(std::max(rgba.x, rgba.y), rgba.z);
    float min = std::min(std::min(rgba.x, rgba.y), rgba.z);
    float diff = max - min;
    
    float hue = 0;
    float saturation = 0;

    if (!CmpFloat(diff, 0)) {
        // Red
        if (max == rgba.x) {
            hue = ((rgba.y - rgba.z) / diff);
        }
        // Green
        if (max == rgba.y) {
            hue = 2 + (rgba.z - rgba.x) / diff;
        }
        // Blue
        if (max == rgba.z) {
            hue = 4 + (rgba.x - rgba.y) / diff;
        }
        if (!CmpFloat(max, 0)) {
            saturation = diff / max;
        }
    }

    hue *= 60;

    return {
            hue < 0 ? hue + 360 : hue,
            saturation * 100,
            max * 100,
            rgba.t
    };
}

//*************************************************************
