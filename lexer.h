#ifndef LEXER_H
#define LEXER_H

#include <cstdio>

typedef enum {
    SEMI_COLON,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
} TypeSeparator;

typedef enum {
    EXIT,
    IDENTIFIER,
    INVALID_KEYWORD
} TypeKeyword;

typedef enum {
    INT,
} TypeLiteral;

typedef enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    EQUAL,
    INVALID_OPERATOR
} TypeOperator;

typedef struct {
    TypeSeparator type;
} TokenSeparator;

typedef struct {
    TypeKeyword type;
    char* value;
} TokenKeyword;

typedef struct {
    TypeLiteral type;
    char* value;
} TokenLiteral;

typedef struct {
    TypeOperator type;
} TokenOperator;

// Function prototypes
char generate_number(char current, FILE* filepoint, TokenLiteral** token_out);
char generate_keyword_or_identifier(char current, FILE* filepoint, TokenKeyword** token_out);
char generate_operator(char current, FILE* filepoint, TokenOperator** token_out);
void lexer(FILE* filepoint);

#endif // LEXER_H
#pragma once
