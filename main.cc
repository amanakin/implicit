// main.cc

#include <vector>
#include <int.h>
#include <logger.h>
#include <utils.h>

#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)

Int funcCopy(Int some) {
    VAR_INT(tmp, 10);
    return some + tmp;
}

Int funcRef(Int& some) {
    VAR_INT(tmp, 10);
    return some + tmp;
}

void SimpleTest() {

};

void SortTest() {
    std::vector<Int> array(100);
    for (auto& el: array) {
        el = Int(std::rand() % 200);
    }

    std::stable_sort(array.begin(), array.end());
};

int main() {
    try {
        Logger::createLogger("log_file.html");
        Logger::setTimeCtrl(false);
        Logger::log("Log file createad " + CurrentDateTime());
    } catch (std::exception& err) {
        std::cerr << err.what() << '\n';
    }

    {
        SortTest();
    }

    Logger::deleteLogger();
}