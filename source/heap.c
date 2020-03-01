#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/heap.h"

/**
 * Creates a new heap data structure
 *
 * @param maxSize the maximum size of the heap. Note: the size is adjusted to the nearest power of 2 to accommodate
 *                the requested size
 * @param compare the comparison function to use
 * @return a pointer to the new heap data structure
 */
HEAP *heapCreate(int maxSize, int (*compare)(void *value1, void *value2)) {
    HEAP *heap;

    heap = (HEAP *)malloc(sizeof(HEAP));
    if (!heap) {
        return NULL;
    }

    heap->size = 0;
    heap->last = -1;
    heap->compare = compare;
    heap->maxSize = (int)pow(2, ceil(log2(maxSize))) - 1;
    heap->data = (void *)calloc(heap->maxSize, sizeof(void *));

    return heap;
}

/**
 * Inserts a new element into the heap
 *
 * @param heap a pointer to the heap
 * @param data a pointer to the element to be added to the heap
 * @return true if successful; false otherwise
 */
bool heapInsert(HEAP *heap, void *data) {
    if (heap->size == 0) {
        heap->size = 1;
        heap->last = 0;
        heap->data[heap->last] = data;
        return true;
    }

    if (heap->last == heap->maxSize - 1) {
        return false;
    }

    heap->last++;
    heap->size++;
    heap->data[heap->last] = data;
    _reheapUp(heap, heap->last);
    return true;
}

/**
 * Deletes the root of the heap and returns the associated element
 *
 * @param heap    a pointer to the heap
 * @param dataOut a pointer to the element that was at the root
 * @return true if successful; false otherwise
 */
bool heapDelete(HEAP *heap, void **dataOut) {
    if (heap->size == 0) {
        return false;
    }
    *dataOut = heap->data[0];
    heap->data[0] = heap->data[heap->last];
    heap->size--;
    heap->last--;
    _reheapDown(heap, 0);
    return true;
}

/**
 * Reestablishes heap by moving data in child up to correct location in the heap array
 *
 * @param heap     a pointer to the heap
 * @param childLoc the child location to adjust
 */
static void _reheapUp(HEAP *heap, int childLoc) {
    int parent;
    void **heapData;
    void *temp;

    if (childLoc) {
        heapData = heap->data;
        parent = ((childLoc - 1) / 2);
        if (heap->compare(heapData[childLoc], heapData[parent]) > 0) {
            temp = heapData[parent];
            heapData[parent] = heapData[childLoc];
            heapData[childLoc] = temp;
            _reheapUp(heap, parent);
        }
    }
}

/**
 * Reestablished the heap by moving data in a root down to the correct location in the heap array
 *
 * @param heap
 * @param root
 */
static void _reheapDown(HEAP *heap, int root) {
    void *temp;
    void *leftData;
    void *rightData;
    int largeLoc;
    int last;

    last = heap->last;
    if ((root * 2 + 1) <= last) {
        leftData = heap->data[root * 2 + 1];
        if ((root * 2 + 2) <= last) {
            rightData = heap->data[root * 2 + 2];
        } else {
            rightData = NULL;
        }

        if ((!rightData) || heap->compare(leftData, rightData) > 0) {
            largeLoc = root * 2 + 1;
        } else {
            largeLoc = root * 2 + 2;
        }

        if (heap->compare(heap->data[root], heap->data[largeLoc]) < 0) {
            temp = heap->data[root];
            heap->data[root] = heap->data[largeLoc];
            heap->data[largeLoc] = temp;
            _reheapDown(heap, largeLoc);
        }
    }
}