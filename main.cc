// main.cc

#include <vector>
#include <int.h>

#include <logger.h>
#include <graph_logger.h>
#include <utils.h>
#include <rec_cnt.h>

#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)

template <typename T>
struct Test {
    void Put(T&& val) {
    }
};

Int Module(Int &lhs, Int &rhs) {
    RecCnt rec;

    VAR_INT(obj, lhs % rhs);

    return obj;
}

Int funcRef(Int& some) {
    RecCnt rec;
    VAR_INT(ten, 10);
    return some + ten;
}

void RefCopyTest() {
    VAR_INT(var1, 1);
    VAR_INT(var2, 2);
    Int var3 = Module(var1, var2);
};

void SortTest() {
    std::vector<Int> array(100);
    for (auto& el: array) {
        // el = Int(std::rand() % 200);
    }

    std::stable_sort(array.begin(), array.end());
};

int main() {
    std::string LogFilename = "yes_move_yes_nrvo";

    Logger::createLogger("log_file.html");
    Logger::setTimeCtrl(false);
    Logger::log("Log file createad " + CurrentDateTime());

    GraphLogger::createLogger(LogFilename + ".dot");
    GraphLogger::log("digraph graph_file {\nnodesep=1;\n");

    {
        RefCopyTest();
    }

    GraphLogger::log("}\n");
    GraphLogger::deleteLogger();

    Logger::log("");
    Logger::log(StringFormat("%-25s = %llu", "Copy count",              Int::CopyCount_));
    Logger::log(StringFormat("%-25s = %llu", "Move count",              Int::MoveCount_));
    Logger::log(StringFormat("%-25s = %llu", "Temporary objects count", Int::TmpCount_));
    Logger::deleteLogger();

    // popen
    system(("dot -Tpdf " + LogFilename + ".dot -o " + LogFilename + ".pdf").c_str());
}