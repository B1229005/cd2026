#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void appendNode(Node** head, Node** tail, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = c;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        char c = current->data;
        
        if (c == '\n') {
            printf("'\\n' ");
        } else if (c == '\t') {
            printf("'\\t' ");
        } else if (c == ' ') {
            printf("' ' ");
        } else {
            printf("'%c' ", c);
        }
        
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen("main.c", "r");
    if (file == NULL) {
        printf("Error: Cannot open main.c\n");
        return 1;
    }

    Node* head = NULL;
    Node* tail = NULL;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        appendNode(&head, &tail, ch);
    }
    fclose(file);

    printList(head);

    freeList(head);

    return 0;
}
