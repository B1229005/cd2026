#include <stdio.h>
#include <string.h>

typedef enum {
    TOKEN_NUM,
    TOKEN_PLUS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

TokenType lookahead;

TokenType getToken() {
    int c;
    while ((c = getchar()) != EOF) {
        
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        }

        if (c >= '0' && c <= '9') {
            
            while ((c = getchar()) != EOF && (c >= '0' && c <= '9')) {
            }
            if (c != EOF) {
                ungetc(c, stdin);
            }
            return TOKEN_NUM;
        }

        if (c == '+') return TOKEN_PLUS;
        if (c == '(') return TOKEN_LPAREN;
        if (c == ')') return TOKEN_RPAREN;

        return TOKEN_ERROR;
    }
    return TOKEN_EOF;
}

void match() {
    lookahead = getToken();
}

void parse_S();
void parse_S_prime();
void parse_E();

void parseError() {
    printf("ParseError\n");
}

void parse_S() {
    printf("parse_S\n"); 
    
    if (lookahead == TOKEN_NUM || lookahead == TOKEN_LPAREN) {
        parse_E();
        parse_S_prime();
    } else {
        parseError();
    }
}

void parse_S_prime() {
    printf("parse_S'\n"); 
    
    if (lookahead == TOKEN_PLUS) {
        match();
        parse_S();
    } 
    else if (lookahead == TOKEN_RPAREN || lookahead == TOKEN_EOF) {
        return;
    } 
    else {
        parseError();
    }
}

void parse_E() {
    printf("parse_E\n");
    
    if (lookahead == TOKEN_NUM) {
        match(); 
    } 
    else if (lookahead == TOKEN_LPAREN) {
        match(); 
        parse_S(); 
        
        if (lookahead == TOKEN_RPAREN) {
            match();
        } else {
            parseError();
        }
    } 
    else {
        parseError();
    }
}

int main() {
    if (freopen("test.txt", "r", stdin) == NULL) {
        printf("找不到 test.txt\n");
        return 1;
    }

    match();
    parse_S();

    return 0;
}
