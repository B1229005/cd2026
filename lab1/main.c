#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    struct Node* next;
} Node;

int main() {
    Node* head = NULL;
    Node* tail = NULL;

    FILE* file = fopen("main.c", "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("記憶體配置失敗\n");
            fclose(file);
            return 1;
        }
        newNode->character = (char)c;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    fclose(file);

    Node* current = head;
    while (current != NULL) {
        if (current->character == '\n') {
            printf("'\\n' ");
        } else if (current->character == '\t') {
            printf("'\\t' ");
        } else if (current->character == ' ') {
            printf("' ' "); 
        } else {
            printf("'%c' ", current->character);
        }
        current = current->next;
    }
    printf("\n");

    current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
