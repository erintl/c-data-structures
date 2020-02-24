#include <stdio.h>
#include <stdlib.h>
#include "header/list.h"

int compare(void *arg1, void *arg2);

int main() {
    int *value;
    int found;
    LIST *list;
    list = createList(compare);

    for (int i = 0; i < 10; i++) {
        value = (int *)malloc(sizeof(int));
        *value = i;
        addNode(list, value);
        printf("List count: %d\n", listCount(list));
    }

    int j = 0;
    while (traverse(list, j, (void *)&value)){
        printf("The traversed value is: %d\n", *value);
        j++;
    }


    destroyList(list);
//    for (int k = 0; k < 10; k++) {
//        found = removeNode(list, (void *)&k, (void *)&value);
//        printf("Remove found: %d, value: %d\n", found, *value);
//        printf("List count: %d\n", listCount(list));
//        free(value);
//    }
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