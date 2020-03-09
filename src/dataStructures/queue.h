#ifndef C_DATA_STRUCTURES_QUEUE_H
#define C_DATA_STRUCTURES_QUEUE_H

#include <stdbool.h>

// type definitions
typedef struct node {
    void *data;
    struct node *next;
} QUEUE_NODE;

typedef struct queue {
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
    int count;
} QUEUE;

// function prototypes
QUEUE *createQueue();
QUEUE *destroyQueue(QUEUE *queue);
bool dequeue(QUEUE *queue, void **item);
bool enqueue(QUEUE *queue, void *item);
bool queueFront(QUEUE *queue, void **item);
bool queueRear(QUEUE *queue, void **item);
int queueCount(QUEUE *queue);
bool emptyQueue(QUEUE *queue);
bool fullQueue(QUEUE *queue);

#endif //C_DATA_STRUCTURES_QUEUE_H
