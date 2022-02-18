// utils.cc

#include <utils.h>
#include <chrono>

std::string currentDateTime() {
    auto currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timeStr = std::ctime(&currTime);
    timeStr[std::strlen(timeStr) - 1] = '\0';

    return timeStr;
}

