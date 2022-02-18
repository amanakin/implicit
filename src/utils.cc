// utils.cc

#include <utils.h>
#include <chrono>
#include <iomanip>
#include <sstream>

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
