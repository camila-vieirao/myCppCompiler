#include <iostream>

// ------- ENUM --------
typedef enum {
    SEMI_COLON,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,

} TypeSeparator;

typedef enum {
    EXIT,
} TypeKeyword;

typedef enum {
    INT,
} TypeLiteral;

// ------- STRUCT --------

typedef struct {
    TypeSeparator type;
} TokenSeparator;

typedef struct {
    TypeKeyword type;
} TokenKeyword;

typedef struct {
    TypeLiteral type;
    int value;
} TokenLiteral;

// ------- LEXER --------

static void lexer(FILE* filepoint) {
    char current = fgetc(filepoint);

    while (current != EOF) {
        if (current == ';') {
            printf("FOUND SEMICOLON\n");
        }
        else if (current == '(') {
            printf("FOUND OPEN PARENTHESIS\n");
        }
        else if (current == ')') {
            printf("FOUND CLOSE PARENTHESIS\n");
        }
        current = fgetc(filepoint);
    }
}
// ------- MAIN --------

int main() {
    FILE* filepoint;
    errno_t err = fopen_s(&filepoint, "test.unn", "r"); // Open file for reading

    if (err != 0) {
        printf("Failed to open file\n");
        return 1;
    }

    lexer(filepoint);

    fclose(filepoint); // Close the file after reading
    return 0;
}