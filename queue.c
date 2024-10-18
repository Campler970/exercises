#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node *front; //队列头
    Node *rear;  //队列尾
} Queue;

void init_queue(Queue* queue) 
{
    queue -> front = NULL;
    queue -> rear = NULL;
}

void push_queue(Queue* queue, int value) 
{
    Node* new_node = NULL;

    if ((new_node = (Node *)malloc(sizeof(Node))) == NULL) {
        printf("fail to malloc \n");
        return;
    }
    
    new_node -> data = value;
    new_node -> next = NULL;
    
    if (queue -> front == NULL) {
        queue -> rear = new_node;
        queue -> front = queue -> rear;
    } else {
        queue -> rear -> next = new_node;
        queue -> rear = new_node; 
    }
}

void pop_queue(Queue *queue, int *data) 
{
    Node *node = NULL;

    if (queue -> rear == NULL) {
        printf("Queue is empty \n");
        return;
    }
    
    if (data == NULL) {
        printf("data can not be null \n");
        return;
    }

    node = queue -> front;
    *data = node -> data;
    queue -> front = queue -> front -> next;

    free (node);
}

void display_queue(Queue *queue)
{
    Node *node = NULL;
    
    node = queue -> front;
    if (queue -> front == NULL) {
        printf("Queue is empty \n");
        return ;
    }

    printf("Queue is :");
    while (node != NULL)
    {
        printf("%d ", node -> data);
        node = node -> next;  
    }
    printf("\n");
}

int main()
{
    Queue *queue = {0};

    init_queue(&queue);

    push_queue(&queue, 10);
    push_queue(&queue, 20);
    push_queue(&queue, 30);
    display_queue(&queue);

    return 0;
}