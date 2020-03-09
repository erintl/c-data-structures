#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * Creates a list
 *
 * @param compare a pointer to the comparision function to be used
 * @return a pointer to the newly created list
 */
LIST *createList(int (*compare)(void *arg1, void *arg2)) {
    LIST *list;

    list = (LIST *)malloc(sizeof(LIST));
    if (list) {
        list->head = NULL;
        list->pos = NULL;
        list->rear = NULL;
        list->count = 0;
        list->compare = compare;
    }
    return list;
}

/**
 * Adds a new element to the list
 *
 * @param list a pointer to the list
 * @param data a pointer to the element to add to the list
 * @return -1 if overflow; O if successful; 1 if duplicate key
 */
int addNode(LIST *list, void *data) {
    bool found = false;
    bool successful = false;
    NODE *preNode = NULL;
    NODE *curNode = NULL;

    found = _search(list, &preNode, &curNode, data);
    if (found) {
        return 1;
    }

    successful = _insert(list, preNode, data);
    if (!successful) {
        return -1;
    }
    return 0;
}

/**
 * Remove a node from the list having the specified key
 *
 * @param list    a pointer to the list
 * @param key     a pointer to the key of the element to remove
 * @param dataOut a double pointer to the removed element
 * @return true if the target element was found; false otherwise
 */
bool removeNode(LIST *list, void *key, void **dataOut) {
    bool found;
    NODE *preNode;
    NODE *curNode;

    found = _search(list, &preNode, &curNode, key);
    if (found) {
        _delete(list, preNode, curNode, dataOut);
    }
    return found;
}

/**
 * Searches for a node with the specified key
 *
 * @param list    a pointer to the list
 * @param key     a pointer to the key
 * @param dataOut a double pointer to the target node's data (if found)
 * @return true if found; false otherwise
 */
bool searchList(LIST *list, void *key, void **dataOut) {
    bool found;
    NODE *preNode;
    NODE *targetNode;
    found = _search(list, &preNode, &targetNode, key);
    if (found) {
        *dataOut = targetNode->data;
    } else {
        *dataOut = NULL;
    }
    return found;
}

/**
 * Returns the contents of a node with a specified key
 *
 * @param list    a pointer to the list
 * @param key     a pointer to the key
 * @param dataOut a double pointer to the target node's data (if found)
 * @return true if found; false otherwise
 */
bool retrieveNode(LIST *list, void *key, void **dataOut) {
    bool found;
    NODE *preNode;
    NODE *targetNode;
    found = _search(list, &preNode, &targetNode, key);
    if (found) {
        *dataOut = targetNode->data;
    } else {
        *dataOut = NULL;
    }
    return found;
}

/**
 * Checks if a list is empty
 *
 * @param list a pointer to the list
 * @return true if empty; false otherwise
 */
bool emptyList(LIST *list) {
    return list->count == 0;
}

/**
 * Returns true if the list is full (an additional node cannot be allocated).
 *
 * @param list a pointer to the list
 * @return true if the list is full; false otherwise
 */
bool fullList(LIST *list) {
    NODE *temp;

    if ((temp = (NODE *)malloc(sizeof*(list->head)))) {
        free(temp);
        return false;
    }
    return true;
}

/**
 * Returns the number of elements in the list
 *
 * @param list a pointer to the list
 * @return the number of elements in the list
 */
int listCount(LIST *list) {
    return list->count;
}

/**
 * Traverses a linked list
 *
 * @param list      a pointer to the list
 * @param fromWhere 0 to begin from the first node
 * @param dataOut   a double pointer to the data of the current node
 * @return true if next node located; false otherwise
 */
bool traverse(LIST *list, int fromWhere, void **dataOut) {
    if (list->count == 0) {
        return false;
    }

    if (fromWhere == 0) {
        list->pos = list->head;
        *dataOut = list->pos->data;
        return true;
    } else {
        if (list->pos->link == NULL) {
            return false;
        } else {
            list->pos = list->pos->link;
            *dataOut = list->pos->data;
            return true;
        }
    }
}

/**
 * Destroys a linked list and frees all associated memory
 *
 * @param list a pointer to the list
 * @return a pointer
 */
LIST *destroyList(LIST *list) {
    NODE *currentNode;

    if (list) {
        while (list->count > 0) {
            free(list->head->data);
            currentNode = list->head;
            list->head = list->head->link;
            list->count--;
            free(currentNode);
        }
        free(list);
    }
    return NULL;
}

/**
 * Utility function used to search for a node having the specified key
 *
 * @param list    a pointer to the list
 * @param preNode the previous node
 * @param curNode the node having the specified key
 * @param key the key of the node to find
 * @return true if found; false otherwise
 * @return true if found; false otherwise
 */
static bool _search(LIST *list, NODE **preNode, NODE **curNode, void *key) {
    int result;

    *preNode = NULL;
    *curNode = list->head;
    if (list->count == 0) {
        return false;
    }

    if ((*list->compare)(key, list->rear->data) > 0) {
        *preNode = list->rear;
        *curNode = NULL;
        return false;
    }

    while ((result = (*list->compare)(key, (*curNode)->data)) > 0) {
        *preNode = *curNode;
        *curNode = (*curNode)->link;
    }

    if (result == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Utility function for inserting a new node into a list
 *
 * @param list    a pointer to the list
 * @param preNode the previous node
 * @param data    the data to be inserted into a new node
 * @return true if successful; false otherwise
 */
static bool _insert(LIST *list, NODE *preNode, void *data) {
    NODE *newNode;

    if (!(newNode = (NODE *)malloc(sizeof(NODE)))) {
        return false;
    }
    newNode->data = data;
    newNode->link = NULL;

    if (preNode == NULL) {
        newNode->link = list->head;
        list->head = newNode;
        if (list->count == 0) {
            list->rear = newNode;
        }
    } else {
        newNode->link = preNode->link;
        preNode->link = newNode;

        if (newNode->link == NULL) {
            list->rear = newNode;
        }
    }
    (list->count)++;
    return true;
}

/**
 * Utility function for deleting a node from a list
 *
 * @param list    a pointer to the list
 * @param preNode the previous node
 * @param curNode the node to be deleted
 * @param dataOut a double pointer to the data contained by the removed element
 */
void _delete(LIST *list, NODE *preNode, NODE *curNode, void **dataOut) {
    *dataOut = curNode->data;
    if (preNode == NULL) {
        list->head = curNode->link;
    } else {
        preNode->link = curNode->link;
    }

    if (curNode->link == NULL) {
        list->rear = preNode;
    }
    (list->count)--;
    free(curNode);
}