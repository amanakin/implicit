// utils.cc

#include <chrono>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstring>

#include <utils.h>

static const float FLOAT_ACCURACY = 0.01;

std::string CurrentDateTime() {
    auto currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timeStr = std::ctime(&currTime);
    timeStr[std::strlen(timeStr) - 1] = '\0';

    return timeStr;
}

std::string IntToHex(uint64_t val) {
    val = val % 0x1000000;
    std::stringstream stream;
    stream << std::hex << val;
    std::string result(stream.str());

    return result;
}

bool CmpFloat(float a, float b) {
    if (!std::isfinite(a) || !std::isfinite(b)) {
        return false;
    }
    return fabs(a - b) < FLOAT_ACCURACY;
}

int HexToDec(unsigned char c) {
    if (c >= '0' && c <= '9') {
        return c - '1';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        // error
        return 0;
    }
}
