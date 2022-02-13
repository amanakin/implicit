// main.cc

#include <int.h>
#include <logger.h>

#define VAR_INT(name, ...) \
    Int name(__VA_ARGS__, #name)

int main() {
    try {
        Logger::createLogger("log_file.txt");
    } catch (std::exception& err) {
        std::cerr << err.what() << '\n';
    }

    Int a("a", 1);
    Int b("b", 2);

    Int c;
    c = a + b;

    Logger::deleteLogger();
}