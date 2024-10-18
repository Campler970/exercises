#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100  

typedef struct Stack{
    int arr[MAX];  // 存储栈元素的数组
    int top;       // 指向栈顶元素的索引
} Stack;

void init_stack(Stack *s) 
{
    s->top = -1;  // 栈为空，设置栈顶为 -1
}

int push_stack(Stack *stack, int value)
{
    if (stack == NULL) {
        printf("Stack can not be null \n");
        return -1;
    }

    if (stack -> top == MAX -1) {
        printf("Stack is full, unable to push %d \n", value);
        return -1;
    }

    stack -> arr[++ stack->top] = value;
    return 0;
}

int pop_stack(Stack *stack, int *value)
{
    if (stack == NULL) {
        printf("Stack can not be null \n");
        return -1;
    }

    if (stack -> top == -1) {
        printf("Stack is empty, unable to pop \n");
        return -1;
    }

    *value = stack -> arr[stack->top --];
    return 0;
}

int peek_stack(Stack *stack, int *value)
{
    if (stack == NULL) {
        printf("Stack can not be null \n");
        return -1;
    }

    if (stack -> top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    
    *value = stack -> arr[stack -> top];
    return 0;
}

int print_stack(Stack *stack)
{
    int i = 0;
    if (stack == NULL) {
        printf("Stack can not be null \n");
        return -1;
    }

    if (stack -> top == -1) {
        printf("Stack is empty\n");
        return -1;
    }

    printf("Stack elements: ");
    for (i = 0; i <= stack->top; i++) {
        printf("%d ", stack -> arr[i]);
    }
    printf("\n");
    return 0;
}

int main() {
    Stack *stack = NULL;
    
    if ((stack = (Stack *)malloc(sizeof(Stack))) == NULL) {
        printf("fail to malloc \n");
        return -1;
    }
    init_stack(stack);

    if(push_stack(stack, 10)!= 0) {
        printf("fail to push \n");
        return -1;
    }
    if(push_stack(stack, 20)!= 0) {
        printf("fail to push \n");
        return -1;
    }
    if(push_stack(stack, 30)!= 0) {
        printf("fail to push \n");
        return -1;
    }

    if(print_stack(stack) != 0) {
        printf("fail to print \n");
        return -1;
    }

    return 0;
}