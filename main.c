#include <stdio.h>
#include <stdlib.h>
#include "header/heap.h"

int compare(void *arg1, void *arg2);
void printArray(int *values, int size);
void reverseArray(int *values, int size);

int main() {
    int size = 10;
    int *values;

    values = (int *)calloc(10, sizeof(int));

    for (int i = 0; i < 10; i++) {
        values[i] = i + 1;
    }

    printArray(values, size);
    reverseArray(values, size);
    printArray(values, size);
    free(values);
}

void printArray(int *values, int size) {
    for (int i = 0; i < size; i++) {
        printf("value[%d]: %d\n", i, values[i]);
    }
}

void reverseArray(int *values, int size) {
    int temp = 0;
    for (int i = 0; i < (size - 1) / 2; i++) {
        temp = values[i];
        values[i] = values[size - i - 1];
        values[size - i - 1] = temp;
    }
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
