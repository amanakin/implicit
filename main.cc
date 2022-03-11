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


template <class _Tp>
_Tp&&
my_forward(typename std::remove_reference<_Tp>::type& __t) _NOEXCEPT
{
    std::cout << "lval forward\n";
    return static_cast<_Tp&&>(__t);
}

template <class _Tp>
_Tp&&
my_forward(typename std::remove_reference<_Tp>::type&& __t) _NOEXCEPT
{
    std::cout << "rval forward\n";
    static_assert(!std::is_lvalue_reference<_Tp>::value,
                  "can not forward an rvalue as an lvalue");
    return static_cast<_Tp&&>(__t);
}



// bad_pair_together
template <typename Tl, typename Tr>
struct Pair {
    template <typename Ul, typename Ur>
    Pair(Ul&& lhs, Ur&& rhs) :
            lhs_(std::forward<Ul>(lhs)), rhs_(std::forward<Ur>(rhs))
    {}

private:
    Tl lhs_;
    Tr rhs_;
};

int main() {

    std::string LogFilename = "good_pair";
    Logger::createLogger("log_file.html");
    Logger::setTimeCtrl(false);
    Logger::log("Log file createad " + CurrentDateTime());

    GraphLogger::createLogger(LogFilename + ".dot");
    GraphLogger::log("digraph graph_file {\nnodesep=1;\n");

    {
        VAR_INT(a, 42);

        Pair<Int, Int> mystic_pair(a, Int(12));
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
    system(("cp " + LogFilename + ".svg ../examples/").c_str());
}