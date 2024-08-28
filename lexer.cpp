#include "lexer.h"
#include <iostream>
#include <cstring> // strcmp and _strdup
#include <cctype>  //isdigit and isalpha

char generate_number(char current, FILE* filepoint, TokenLiteral** token_out) {
    TokenLiteral* token = new TokenLiteral();
    token->type = INT;
    char* value = new char[8];
    int value_index = 0;
    while (isdigit(current) && current != EOF) {
        value[value_index] = current;
        value_index++;
        current = fgetc(filepoint);
    }
    value[value_index] = '\0';
    token->value = value;
    *token_out = token;
    return current;
}

char generate_keyword_or_identifier(char current, FILE* filepoint, TokenKeyword** token_out) {
    TokenKeyword* token = new TokenKeyword();
    char keyword[256] = { 0 };
    int keyword_index = 0;
    bool is_invalid = false;

    while (isalpha(current) && current != EOF) {
        if (keyword_index < 255) {
            keyword[keyword_index] = current;
        }
        else {
            is_invalid = true;
        }
        keyword_index++;
        current = fgetc(filepoint);
    }
    keyword[keyword_index] = '\0';

    if (strcmp(keyword, "exit") == 0 && !is_invalid) {
        token->type = EXIT;
        token->value = nullptr;
    }
    else if (!is_invalid) {
        token->type = IDENTIFIER;
        token->value = _strdup(keyword);
    }
    else {
        token->type = INVALID_KEYWORD;
        token->value = nullptr;
    }

    *token_out = token;
    return current;
}

char generate_operator(char current, FILE* filepoint, TokenOperator** token_out) {
    TokenOperator* token = new TokenOperator();

    if (current == '+') {
        token->type = PLUS;
    }
    else if (current == '-') {
        token->type = MINUS;
    }
    else if (current == '*') {
        token->type = MULTIPLY;
    }
    else if (current == '/') {
        token->type = DIVIDE;
    }
    else if (current == '=') {
        char next = fgetc(filepoint);
        if (next == '=') {
            token->type = EQUAL;
        }
        else {
            token->type = ASSIGN;
            ungetc(next, filepoint);
        }
    }
    else {
        token->type = INVALID_OPERATOR;
    }

    *token_out = token;
    return fgetc(filepoint);
}

void lexer(FILE* filepoint) {
    char current = fgetc(filepoint);

    while (current != EOF) {
        if (current == ';') {
            std::cout << "FOUND SEMICOLON\n";
        }
        else if (current == '(') {
            std::cout << "FOUND OPEN PARENTHESIS\n";
        }
        else if (current == ')') {
            std::cout << "FOUND CLOSE PARENTHESIS\n";
        }
        else if (isdigit(current)) {
            TokenLiteral* test_token = nullptr;
            current = generate_number(current, filepoint, &test_token);
            std::cout << "NUMBER: " << test_token->value << "\n";
            delete[] test_token->value;
            delete test_token;
            continue;
        }
        else if (isalpha(current)) {
            TokenKeyword* keyword_token = nullptr;
            current = generate_keyword_or_identifier(current, filepoint, &keyword_token);
            if (keyword_token->type == EXIT) {
                std::cout << "FOUND KEYWORD: EXIT\n";
            }
            else if (keyword_token->type == IDENTIFIER) {
                std::cout << "IDENTIFIER: " << keyword_token->value << "\n";
                delete[] keyword_token->value;
            }
            else if (keyword_token->type == INVALID_KEYWORD) {
                std::cout << "INVALID KEYWORD\n";
            }
            delete keyword_token;
            continue;
        }
        else if (strchr("+-*/=", current)) {
            TokenOperator* operator_token = nullptr;
            current = generate_operator(current, filepoint, &operator_token);
            switch (operator_token->type) {
            case PLUS:
                std::cout << "FOUND OPERATOR: PLUS\n";
                break;
            case MINUS:
                std::cout << "FOUND OPERATOR: MINUS\n";
                break;
            case MULTIPLY:
                std::cout << "FOUND OPERATOR: MULTIPLY\n";
                break;
            case DIVIDE:
                std::cout << "FOUND OPERATOR: DIVIDE\n";
                break;
            case ASSIGN:
                std::cout << "FOUND OPERATOR: ASSIGN\n";
                break;
            case EQUAL:
                std::cout << "FOUND OPERATOR: EQUAL\n";
                break;
            default:
                std::cout << "INVALID OPERATOR\n";
            }
            delete operator_token;
            continue;
        }
        current = fgetc(filepoint);
    }
}
