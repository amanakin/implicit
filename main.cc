// main.cc

#include <vector>
#include <int.h>
#include <type_traits>

#include <logger.h>
#include <graph_logger.h>
#include <utils.h>
#include <rec_cnt.h>

#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)

Int AddWithBound(const Int& a, const Int& b) {
    VAR_INT(res, a + b);
    if (res > 1000) {
        res = 1000;
    } else if (res < 0) {
        res = 0;
    }

    return std::move(res);
}

int main() {

    std::string LogFilename = "yes_move_yes_nrvo_bad_move";
    Logger::createLogger("log_file.html");
    Logger::setTimeCtrl(false);
    Logger::log("Log file createad " + CurrentDateTime());

    GraphLogger::createLogger(LogFilename + ".dot");
    GraphLogger::log("digraph graph_file {\nnodesep=1;\n");

    {
        VAR_INT(a, 500);
        VAR_INT(b, 1000);

        Int c = AddWithBound(a, b);

        std::is_constant_evaluated();
    }

    GraphLogger::log("}\n");
    GraphLogger::deleteLogger();

    Logger::log("");
    Logger::log(StringFormat("%-25s = %llu", "Copy count",              Int::CopyCount_));
    Logger::log(StringFormat("%-25s = %llu", "Move count",              Int::MoveCount_));
    Logger::log(StringFormat("%-25s = %llu", "Temporary objects count", Int::TmpCount_));
    Logger::deleteLogger();

    // popen
    system(("dot -Tsvg " + LogFilename + ".dot -o " + LogFilename + ".svg").c_str());
}