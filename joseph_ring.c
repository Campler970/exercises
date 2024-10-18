#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int num;
    struct Node *next;
}Member_Node;

int get_last_member(int n, int m)
{
    int i = 0;
    int j = 0;
    int result = 0;
    Member_Node *head = NULL;
    Member_Node *tail = NULL;
    Member_Node *p = NULL;
    Member_Node *q = NULL;

    if(n == 0 || m == 0){
        printf("arguments error\n");
        return 0;
    }

    if((head = (Member_Node* ) malloc (sizeof(Member_Node))) == NULL){
        printf("fail to malloc\n");
        return 0;
    }
    
    head -> num = 1;
    tail = head;  //循环链表尾节点和头结点为同一个

    for(i = 2; i <= n; i++){
        if((tail -> next = (Member_Node* ) malloc (sizeof(Member_Node))) == NULL){
            printf("fail to malloc\n");
            return 0;
        }
        tail = tail -> next;
        tail -> num = i;
    }

    tail -> next = head;
    p = head;

    while (p-> next != p){
        for (i =1; i < m -1; i++) {
            p = p -> next;
        }      
        q = p -> next;
        p -> next = q -> next;
        free(q);
        p = p -> next;
    }
    result = p -> num;
    free(p);
    return result;
    
}
int main()
{
    int result = 0;
    if((result = get_last_member(5, 2)) == 0) {
        printf("fail to get result \n");
        return -1;
    }
    printf("the last one is %d\n", result);
    return 0;
}