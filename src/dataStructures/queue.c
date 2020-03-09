#include <stdlib.h>
#include "queue.h"

/**
 * Allocates and returns a queue head node
 *
 * @return a new queue head node
 */
QUEUE *createQueue(void) {
    QUEUE *queue;

    queue = (QUEUE *)malloc(sizeof(QUEUE));
    if (queue) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }
    return queue;
}

/**
 * Inserts a provided item into the queue
 *
 * @param queue the queue to insert an item into
 * @param item  the item to be inserted into the queue
 * @return true is successful; false otherwise
 */
bool enqueue(QUEUE *queue, void *item) {
    QUEUE_NODE *newNode;

    newNode = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
    if (!newNode) {
        return false;
    }

    newNode->data = item;
    newNode->next = NULL;

    if (queue->count == 0) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    (queue->count)++;
    queue->rear = newNode;
    return true;
}

/**
 * Queues an item from the queue
 *
 * @param queue the queue to retrieve an item from
 * @param item  the item to be retrieved
 * @return true if successful; false otherwise
 */
bool dequeue(QUEUE *queue, void **item) {
    QUEUE_NODE *node;

    if (!queue->count) {
        return false;
    }

    *item = queue->front->data;
    node = queue->front;
    if (queue->count == 1) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    (queue->count)--;
    free(node);
    return true;
}

/**
 * Returns the element at the front of the queue, without modifying the queue.
 *
 * @param item the returned item
 * @return true if successful; false otherwise
 */
bool queueFront(QUEUE *queue, void **item) {
    if (!queue->count) {
        return false;
    }
    *item = queue->front->data;
    return true;
}

/**
 * Returns the element at the rear of the queue, without modifying the queue.
 *
 * @param item the returned item
 * @return true if successful; false otherwise
 */
bool queueRear(QUEUE *queue, void **item) {
    if (!queue->count) {
        return false;
    }
    *item = queue->rear->data;
    return true;
}

/**
 * Checks if the queue is empty. Returns true if empty; false otherwise
 *
 * @param queue the queue to check
 * @return  true if empty; false otherwise
 */
bool emptyQueue(QUEUE *queue) {
    return queue->count == 0;
}

/**
 * Checks if the queue is full.
 *
 * @param queue the queue to check
 * @return true if the queue is full; false otherwise
 */
bool fullQueue(QUEUE *queue) {
    QUEUE_NODE *node;
    node = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
    if (node) {
        free(node);
        return true;
    }
    return false;
}

/**
 * Returns the number of elements in the queue
 *
 * @param queue the queue to check
 * @return the number of elements in the queue
 */
int queueCount(QUEUE *queue) {
    return queue->count;
}

/**
 * Destroys the queue and frees the associated memory.
 *
 * @param queue the queue to destroy
 * @return a null pointer
 */
QUEUE *destroyQueue(QUEUE *queue) {
    QUEUE_NODE *node;

    if (queue) {
        while (queue->front != NULL) {
            node = queue->front;
            queue->front = queue->front->next;
            free(node->data);
            free(node);
        }
     free(queue);
    }
    return NULL;
}
