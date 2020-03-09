#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/**
 * Creates a new BST tree
 *
 * @param compare the compare function to use
 * @return a pointer to a new BST tree head structure
 */
BST_TREE *bstCreate(int (*compare)(void *value1, void *value2)) {
    BST_TREE *tree;

    tree = (BST_TREE *)malloc(sizeof(BST_TREE));
    if (tree) {
        tree->root = NULL;
        tree->count = 0;
        tree->compare = compare;
    }
    return tree;
}

/**
 * Inserts an element into a BST tree
 *
 * @param tree a pointer to the tree
 * @param data a pointer to the element to insert
 * @return true if successful; false otherwise
 */
bool bstInsert(BST_TREE *tree, void *data) {
    NODE *newNode;

    newNode = (NODE *)malloc(sizeof(NODE));
    if (!newNode) {
        return false;
    }
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;

    if (tree->count == 0) {
        tree->root = newNode;
    } else {
        _insert(tree, tree->root, newNode);
    }
    tree->count++;
    return true;
}

/**
 * Deletes a specified node in a BST tree
 *
 * @param tree a pointer to the tree
 * @param key  the key of the node to delete
 * @return true if successful; false otherwise
 */
bool bstDelete(BST_TREE *tree, void *key) {
    bool success = false;
    NODE *newRoot;

    newRoot = _delete(tree, tree->root, key, &success);
    if (success) {
        tree->root = newRoot;
        tree->count--;
        if (tree->count == 0) {
            tree->root = NULL;
        }
    }
    return success;
}

/**
 * Retrieves the specified value from a BST tree
 *
 * @param tree a pointer the tree to search
 * @param key  a pointer to the key to find
 * @return a pointer to the element if found; NULL otherwise
 */
void *bstRetrieve(BST_TREE *tree, void *key) {
    if (tree->root) {
        return _retrieve(tree, key, tree->root);
    } else {
        return NULL;
    }
}

void *bstTraverse(BST_TREE *tree, void (*process)(void *data)) {
    _traverse(tree->root, process);
}

/**
 * Destroys a BST tree and frees the associated memory for nodes and elements
 *
 * @param tree a pointer to the tree to destroy
 * @return NULL
 */
BST_TREE *bstDestroy(BST_TREE *tree) {
    if (tree) {
        _destroy(tree->root);
    }
    free(tree);
    return NULL;
}

/**
 * Returns true if the BST tree is empty
 *
 * @param tree a pointer to the tree
 * @return true if empty; false otherwise
 */
bool bstEmpty(BST_TREE *tree) {
    return tree->count == 0;
}

/**
 * Returns true if the BST true is full (memory for another node cannot be allocated)
 *
 * @param tree a pointer to the tree
 * @return true if full; false otherwise
 */
bool fullBst(BST_TREE *tree) {
    NODE *node;

    node = (NODE *)malloc(sizeof(*(tree->root)));
    if (node) {
        free(node);
        return false;
    }
    return true;
}

/**
 * Returns the number of nodes in the BST tree
 *
 * @param tree a pointer to the tree
 * @return the number of nodes in the BST tree
 */
int bstCount(BST_TREE *tree) {
    return tree->count;
}

/**
 * A recursive utility function for inserting a node into a BST tree
 *
 * @param tree    a pointer to the tree
 * @param root    the root node
 * @param newNode the node to be inserted into the tree
 * @return a pointer to the node to be inserted
 */
static NODE *_insert(BST_TREE *tree, NODE *root, NODE *newNode) {
    if (!root) {
        return newNode;
    }
    if (tree->compare(newNode->data, root->data) < 0) {
        root->left = _insert(tree, root->left, newNode);
        return root;
    } else {
        root->right = _insert(tree, root->right, newNode);
        return root;
    }
}

/**
 * A recursive utility function for destroying a BST tree and freeing the associated memory
 *
 * @param root the root node to destroy
 */
static void _destroy(NODE *root) {
    if (root) {
        _destroy(root->left);
        _destroy(root->right);
        printf("Deleting data for node: %d\n", *(int *)root->data);
        free(root->data);
        free(root);
    }
}

static NODE *_delete(BST_TREE *tree, NODE *root, void *data, bool *success) {
    NODE *exchangeNode;
    NODE *newRoot;
    void *tempData;

    if (!root) {
        *success = false;
        return NULL;
    }

    printf("deleting: %d\n", *(int *)data);
    if (tree->compare(data, root->data) < 0) {
        root->left = _delete(tree, root->left, data, success);
    } else if (tree->compare(data, root->data) > 0) {
        root->right = _delete(tree, root->right, data, success);
    } else {
        if (!root->left) {
            newRoot = root->right;
            free(root->data);
            free(root);
            *success = true;
            return newRoot;
        } else if (!root->right) {
            newRoot = root->left;
            free(root->data);
            free(root);
            *success = true;
            return newRoot;
        }
        else {
            exchangeNode = root->left;
            while (exchangeNode->right) {
                exchangeNode = exchangeNode->right;
            }
            tempData = root->data;
            root->data = exchangeNode->data;
            exchangeNode->data = tempData;
            root->left = _delete(tree, root->left, exchangeNode->data, success);
        }
    }
    return root;
}

static void *_retrieve(BST_TREE *tree, void *key, NODE *root) {
    if (root) {
        if (tree->compare(key, root->data) < 0) {
            return _retrieve(tree, key, root->left);
        } else if (tree->compare(key, root->data) > 0) {
            return _retrieve(tree, key, root->right);
        } else {
            return root->data;
        }
    } else {
        return NULL;
    }
}

static void _traverse(NODE *root, void (*process)(void *data)) {
    if (root) {
        _traverse(root->left, process);
        process(root->data);
        _traverse(root->right, process);
    }
}