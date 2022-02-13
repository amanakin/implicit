// utils.cc

#include <utils.h>

std::string currentDateTime() {
    time_t now = time(nullptr);
    tm     calTime = {0};
    char   buf[80] = "";
    calTime = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &calTime);

    return buf;
}

