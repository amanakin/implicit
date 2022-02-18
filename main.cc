// main.cc


#define MOVE_SEMANTICS
#include <int.h>
#include <logger.h>

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



int main() {
    try {
        Logger::createLogger("log_file.txt");
    } catch (std::exception& err) {
        std::cerr << err.what() << '\n';
    }

    VAR_INT(a, 0);
    VAR_INT(b);

    ++a;
    ++b;

    b = funcCopy(a);
    VAR_INT(c);
    c = funcRef(b);

    Logger::deleteLogger();
}