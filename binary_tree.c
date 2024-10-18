#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    int data;
    struct tree_node *left;
    struct tree_node *right;
}Tree_Node;

Tree_Node* create_node(int data)
{
    Tree_Node *new_node = NULL;
    if((new_node = (Tree_Node*)malloc(sizeof(Tree_Node))) == NULL){
        printf("fail to malloc\n");
        return NULL;
    }

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Tree_Node *insert_node(Tree_Node *root, int data)
{
    if (root == NULL){
        root = create_node(data);
    } else if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else {
        root->right = insert_node(root->right, data);
    }
    return root;
}

void pre_order_traversal(Tree_Node *root) { // 先序遍历
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

void in_order_traversal(Tree_Node *root) { // 中序遍历
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%d ", root->data);
        in_order_traversal(root->right);
    }
}

void post_order_traversal(Tree_Node *root) { // 后序遍历
    if (root != NULL) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf("%d ", root->data);
    }
}

void free_tree(Tree_Node *root)
{
    if (root != NULL){
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    Tree_Node *root = NULL;

    root = insert_node(root, 50);
    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 40);
    root = insert_node(root, 70);

    printf("pre_order_traversal is: ");
    pre_order_traversal(root);
    printf("\n");

    printf("in_order_traversal is: ");
    in_order_traversal(root);
    printf("\n");

    printf("post_order_traversal is: ");
    post_order_traversal(root);
    printf("\n");

    // 释放二叉树占用的内存
    free_tree(root);

    return 0;
}
