#ifndef C_DATA_STRUCTURES_HEAP_H
#define C_DATA_STRUCTURES_HEAP_H

#include <stdbool.h>

// type definitions
typedef struct {
    void **data;
    int last;
    int size;
    int (*compare)(void *value1, void *value2);
    int maxSize;
} HEAP;

// function prototypes
HEAP *heapCreate(int maxSize, int (*compare)(void *value1, void *value2));
bool heapInsert(HEAP *heap, void *data);
bool heapDelete(HEAP *heap, void **dataOut);

static void _reheapUp(HEAP* heap, int childLoc);
static void _reheapDown(HEAP *heap, int root);

#endif //C_DATA_STRUCTURES_HEAP_H
