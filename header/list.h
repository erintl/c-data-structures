#ifndef C_DATA_STRUCTURES_LIST_H
#define C_DATA_STRUCTURES_LIST_H

#include <stdbool.h>

// type definitions
typedef struct node {
    void *data;
    struct node *link;
} NODE;

typedef struct list {
    int count;
    NODE *pos;
    NODE *head;
    NODE *rear;
    int (*compare)(void *arg1, void *arg2);
} LIST;

// function prototypes
LIST *createList(int (*compare)(void *arg1, void *arg2));
LIST *destroyList(LIST *list);
int addNode(LIST *list, void *data);
bool removeNode(LIST *list, void *key, void **dataOut);
bool searchList(LIST *list, void *key, void **dataOut);
bool retrieveNode(LIST *list, void *arg, void **dataOut);
bool traverse(LIST *list, int fromWhere, void **dataOut);
int listCount(LIST *list);
bool emptyList(LIST *list);
bool fullList(LIST *list);

static bool _insert(LIST *list, NODE *preNode, void *data);
static void _delete(LIST *list, NODE *preNode, NODE *curNode, void **dataOut);
static bool _search(LIST *list, NODE **preNode, NODE **curNode, void *key);

#endif //C_DATA_STRUCTURES_LIST_H
