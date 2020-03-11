#include <stdlib.h>
#include "unity.h"
#include "list.h"

// Global test variables
static LIST *list;

// test function prototypes
int compare(void *arg1, void *arg2);
void emptyList_returnsTrueForEmptyList();
void emptyList_returnsFalseForNonEmptyList();
void listCount_returnZeroForEmptyList();
void listCount_returnsCorrectCount();

int main() {
    UNITY_BEGIN();
    RUN_TEST(emptyList_returnsTrueForEmptyList);
    RUN_TEST(emptyList_returnsFalseForNonEmptyList);
    RUN_TEST(listCount_returnZeroForEmptyList);
    RUN_TEST(listCount_returnsCorrectCount);

    return UNITY_END();
}

void setUp() {
    list = createList(compare);
}
void tearDown() {
    destroyList(list);
}

int compare(void *arg1, void *arg2) {
    int result;

    if ((int *)arg1 < (int *)arg2) {
        result = -1;
    } else if ((int *)arg1 < (int *)arg2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void emptyList_returnsTrueForEmptyList() {
    TEST_ASSERT_TRUE(emptyList(list));
}

void emptyList_returnsFalseForNonEmptyList() {

}
void listCount_returnZeroForEmptyList() {

}

void listCount_returnsCorrectCount() {

}