#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int count;
    struct Node* next;
} Node;

int main() {
    
    Node* charMap[256] = {NULL}; 
    
    
    Node* head = NULL;
    Node* tail = NULL;

    
    FILE* file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }
int c;
    while ((c = fgetc(file)) != EOF) {
        
        if ((c >= 32 && c <= 126) || c == '\n' || c == '\t') {
            
            if (charMap[c] != NULL) {
                charMap[c]->count++;
            } else {
                Node* newNode = (Node*)malloc(sizeof(Node));
                if (newNode == NULL) {
                    printf("記憶體配置失敗\n");
                    fclose(file);
                    return 1;
                }
                newNode->character = (char)c;
                newNode->count = 1;
                newNode->next = NULL;

                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                charMap[c] = newNode;
            }
        }
    }
    
    fclose(file);

    Node* current = head;
    while (current != NULL) {
        if (current->character == '\n') {
            printf("\\n:%d\n", current->count);
        } else if (current->character == '\t') {
            printf("\\t:%d\n", current->count);
        } else if (current->character == ' ') {
            printf("space:%d\n", current->count);
        } else {
            printf("%c:%d\n", current->character, current->count);
        }
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
