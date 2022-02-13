#include <int.h>

#define VAR_INT(name, ...) \
    Int name(__VA_ARGS__, #name)

int main() {
    Int a("a", 1);
    Int b("b", 2);

    Int c;
    c = a + b;
}