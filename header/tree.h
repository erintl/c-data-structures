#ifndef C_DATA_STRUCTURES_TREE_H
#define C_DATA_STRUCTURES_TREE_H

#include <stdbool.h>

// type definitions
typedef struct node {
    void *data;
    struct node *left;
    struct node *right;
} NODE;

typedef struct {
    int count;
    int (*compare)(void *value1, void *value2);
    NODE *root;
} BST_TREE;

// function prototypes
BST_TREE *bstCreate(int (*compare)(void *value1, void *value2));
BST_TREE *bstDestroy(BST_TREE *tree);
bool bstInsert(BST_TREE *tree, void *data);
bool bstDelete(BST_TREE *tree, void *key);
void *bstRetrieve(BST_TREE *tree, void *key);
void *bstTraverse(BST_TREE *tree, void (*process)(void *data));
bool bstEmpty(BST_TREE *tree);
bool bstFull(BST_TREE *tree);
int bstCount(BST_TREE *tree);

static NODE *_insert(BST_TREE *tree, NODE *root, NODE *newNode);
static void _destroy(NODE *root);
static NODE *_delete(BST_TREE *tree, NODE *root, void *data, bool *success);
static void *_retrieve(BST_TREE *tree, void *key, NODE *root);
static void _traverse(NODE *tree, void (*process)(void *data));

#endif //C_DATA_STRUCTURES_TREE_H
