#include <stdio.h>
#include <stdlib.h>
#include "header/tree.h"

void createNode(BST_TREE *tree, int number);
int compare(void *arg1, void *arg2);
void printNode(void *data);

int main() {
    int key = 3;

    BST_TREE *tree;
    tree = bstCreate(compare);

    createNode(tree, 5);
    createNode(tree, 2);
    createNode(tree, 1);
    createNode(tree, 0);
    createNode(tree, 3);
    createNode(tree, 4);
    createNode(tree, 8);
    createNode(tree, 6);
    createNode(tree, 9);
    createNode(tree, 10);
    createNode(tree, 7);

    bstTraverse(tree, printNode);

    bstDestroy(tree);
}

void createNode(BST_TREE *tree, int number) {
    int *value;
    value = (int *)malloc(sizeof(int));
    *value = number;
    bstInsert(tree, value);
    printf("List count: %d\n", bstCount(tree));
}

int compare(void *arg1, void *arg2) {
    int result;
    int *value1 = (int *)arg1;
    int *value2 = (int *)arg2;

    if (*value1 < *value2) {
        result = -1;
    }
    else if (*value1 > *value2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void printNode(void *data) {
    printf("The node value is: %d\n", *(int *)data);
}