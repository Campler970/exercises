#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void create_node(Node** header, int data)
{
    Node *tailer = NULL;
    Node *node = NULL;
    
    if ((node = (Node*)malloc(sizeof(Node))) == NULL) { 
        printf("fail to malloc");
        return;
    }
    node -> data = data;
    node -> next = NULL;

    if ( *header == NULL) {
        *header = node;
        return;
    }

    tailer = *header;
    while (tailer -> next != NULL) { 
        tailer = tailer -> next;
    }
    tailer -> next = node;
}

void delete_node(Node** header, int data)
{
    Node* pointer = NULL;
    Node* prev = NULL;

    pointer = *header;
    while (pointer != NULL && pointer -> data != data) {
        prev = pointer;
        pointer = pointer -> next;
    }
    if (pointer == NULL) { 
        printf("the data is not in the list\n");
        return;
    }
    if(prev == NULL){
        *header = pointer -> next; //删除第一个节点
    } else {
        prev -> next = pointer -> next;
    }
    
    free(pointer);
}

void update_node(Node *header, int old_data, int new_data)
{
    Node *pointer = NULL;
    pointer = header;
        if(pointer -> data == old_data) {
            pointer -> data = new_data;
            return;
        }
    pointer = pointer -> next;
}

void revert_list(Node** header)
{
    Node* prev = NULL;
    Node* pointer = NULL;
    Node* next = NULL;
    
    pointer = *header;
    while (pointer != NULL) { 
        next = pointer -> next;
        pointer -> next = prev; //倒转节点的指针指向
        prev = pointer;
        pointer = next;
    }
    *header = prev;
}

void display_list(Node *header)
{
    Node* pointer = NULL;
    pointer = header;

    while (pointer != NULL) {
        printf("%d\n", pointer -> data);
        pointer = pointer -> next;
    }  
}

void release_list(Node *header)
{
    Node *pointer = NULL;
    Node *next_node = NULL;

    pointer = header;
    while (pointer != NULL) {
        next_node = pointer -> next;
        free(pointer);
        pointer = next_node;
    }  
}

int main()
{
    Node *header = NULL;

    create_node(&header, 1);
    create_node(&header, 2);
    create_node(&header, 3);
    
    //delete_node(&header,3);
    //update_node(header, 1,11);
    display_list(header);
    revert_list(&header);
    display_list(header);
    release_list(header);

    return 0;
}