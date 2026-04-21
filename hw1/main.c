#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TokenNode {
    char lexeme[256];
    char tokenType[50];
    struct TokenNode* next;
} TokenNode;

TokenNode* head = NULL;
TokenNode* tail = NULL;

void addToken(const char* lex, const char* type) {
    TokenNode* newNode = (TokenNode*)malloc(sizeof(TokenNode));
    strcpy(newNode->lexeme, lex);
    strcpy(newNode->tokenType, type);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

int main() {
	if (freopen("test.c", "r", stdin) == NULL) {
        printf("���~�G�䤣�� test.c �ɮסI�нT�{���⥦�� main.c ��b�P�@�Ӹ�Ƨ��C\n");
        return 1;
    }
    int c;

    while ((c = getchar()) != EOF) {
        
        if (isspace(c)) {
            continue;
        }

        if (isalpha(c) || c == '_') {
            char buffer[256];
            int len = 0;
            buffer[len++] = (char)c;
            
            while ((c = getchar()) != EOF && (isalnum(c) || c == '_')) {
                if (len < 255) buffer[len++] = (char)c;
            }
            buffer[len] = '\0';
            
            ungetc(c, stdin); 

            if (strcmp(buffer, "int") == 0) addToken(buffer, "TYPE_TOKEN");
            else if (strcmp(buffer, "main") == 0) addToken(buffer, "MAIN_TOKEN");
            else if (strcmp(buffer, "if") == 0) addToken(buffer, "IF_TOKEN");
            else if (strcmp(buffer, "else") == 0) addToken(buffer, "ELSE_TOKEN");
            else if (strcmp(buffer, "while") == 0) addToken(buffer, "WHILE_TOKEN");
            else addToken(buffer, "IDENTIFIER_TOKEN");
        }
        else if (isdigit(c)) {
            char buffer[256];
            int len = 0;
            buffer[len++] = (char)c;
            
            while ((c = getchar()) != EOF && isdigit(c)) {
                if (len < 255) buffer[len++] = (char)c;
            }
            buffer[len] = '\0';
            
            ungetc(c, stdin); 
            addToken(buffer, "INTLITERAL");
        }
        else if (c == '=') {
            int next_c = getchar();
            if (next_c == '=') {
                addToken("==", "EQUAL_TOKEN");
            } else {
                ungetc(next_c, stdin); 
                addToken("=", "ASSIGN_TOKEN");
            }
        }
        else if (c == '>') {
            int next_c = getchar();
            if (next_c == '=') {
                addToken(">=", "GREATEREQUAL_TOKEN");
            } else {
                ungetc(next_c, stdin);
                addToken(">", "GREATER_TOKEN");
            }
        }
        else if (c == '(') addToken("(", "LEFTPAREN_TOKEN");
        else if (c == ')') addToken(")", "RIGHTPAREN_TOKEN"); 
        else if (c == '{') addToken("{", "LEFTBRACE_TOKEN");
        else if (c == '}') addToken("}", "RIGHTBRACE_TOKEN");
        else if (c == '+') addToken("+", "PLUS_TOKEN");
        else if (c == ';') addToken(";", "SEMICOLON_TOKEN");
        else {
            char buffer[2] = {(char)c, '\0'};
            addToken(buffer, "UNKNOWN_TOKEN");
        }
    }

    TokenNode* current = head;
    while (current != NULL) {
        printf("%s: %s\n", current->lexeme, current->tokenType);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        TokenNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
