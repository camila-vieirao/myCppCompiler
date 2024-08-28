#include <iostream>
#include "lexer.h"

// ------- MAIN --------

int main() {
    FILE* filepoint;
    errno_t err = fopen_s(&filepoint, "test.unn", "r");

    if (err != 0) {
        std::cout << "Failed to open file\n";
        return 1;
    }

    lexer(filepoint);

    fclose(filepoint);
    return 0;
}
