// main.cc

#include <vector>
#include <int.h>
#include <logger.h>
#include <utils.h>

#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)

Int funcCopy(Int some) {
    VAR_INT(ten, 10);
    return some + ten;
}

Int funcRef(Int& some) {
    VAR_INT(ten, 10);
    return some + ten;
}

void RefCopyTest() {
    VAR_INT(var1, 0);
    VAR_INT(var2, var1);

    Logger::log("Reference:");
    var1 = funcRef(var1);

    Logger::log("Copy:");
    var2 = funcCopy(var2);
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
        RefCopyTest();
    }

    Logger::log("");
    Logger::log(string_format("%-25s = %llu", "Copy count",              Int::CopyCount_));
    Logger::log(string_format("%-25s = %llu", "Move count",              Int::MoveCount_));
    Logger::log(string_format("%-25s = %llu", "Temporary objects count", Int::TmpCount_));

    Logger::deleteLogger();
}