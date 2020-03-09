#include <stdlib.h>
#include "unity.h"
#include "queue.h"

// test prototypes
void emptyQueue_returnsTrueForEmptyQueue();
void emptyQueue_returnsFalseForNonEmptyQueue();
void queueCount_returnsZeroForEmptyQueue();
void queueCount_returnsCorrectCount();
void enqueue_addsElementToQueue();
void queueFront_returnsFalseForEmptyQueue();
void queueFront_returnsTrueForNonEmptyQueue();
void queueFront_returnsFrontElement();
void queueFront_doesNotRemoveElementsFromQueue();
void queueRear_returnsFalseForEmptyQueue();
void queueRear_returnsTrueForNonEmptyQueue();
void queueRear_returnsRearElement();
void queueRear_doesNotRemoveElementsFromQueue();
void fullQueue_returnsFalseIfMemoryCanBeAllocated();
void dequeue_returnsElementsInFifoOrder();


// Global test variables
QUEUE *queue;

int main() {
    UNITY_BEGIN();
    RUN_TEST(emptyQueue_returnsTrueForEmptyQueue);
    RUN_TEST(emptyQueue_returnsFalseForNonEmptyQueue);
    RUN_TEST(queueCount_returnsZeroForEmptyQueue);
    RUN_TEST(queueCount_returnsCorrectCount);
    RUN_TEST(enqueue_addsElementToQueue);
    RUN_TEST(queueFront_returnsFalseForEmptyQueue);
    RUN_TEST(queueFront_returnsTrueForNonEmptyQueue);
    RUN_TEST(queueFront_returnsFrontElement);
    RUN_TEST(queueFront_doesNotRemoveElementsFromQueue);
    RUN_TEST(queueRear_returnsFalseForEmptyQueue);
    RUN_TEST(queueRear_returnsTrueForNonEmptyQueue);
    RUN_TEST(queueRear_returnsRearElement);
    RUN_TEST(queueRear_doesNotRemoveElementsFromQueue);
    RUN_TEST(fullQueue_returnsFalseIfMemoryCanBeAllocated);
    RUN_TEST(dequeue_returnsElementsInFifoOrder);

    return UNITY_END();
}

void setUp() {
    queue = createQueue();
}
void tearDown() {
    destroyQueue(queue);
}

void emptyQueue_returnsTrueForEmptyQueue() {
    TEST_ASSERT_TRUE(emptyQueue(queue));
}

void emptyQueue_returnsFalseForNonEmptyQueue() {
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    enqueue(queue, element);

    TEST_ASSERT_FALSE(emptyQueue(queue));
}

void queueCount_returnsZeroForEmptyQueue() {
    int count;

    count = queueCount(queue);

    TEST_ASSERT_EQUAL_INT(count, 0);
}

void queueCount_returnsCorrectCount() {
    int count;
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    enqueue(queue, element);
    count = queueCount(queue);

    TEST_ASSERT_EQUAL_INT(count, 1);
}

void enqueue_addsElementToQueue() {
    int count;
    int *expectedElement;
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    enqueue(queue, element);
    count = queueCount(queue);
    queueFront(queue, (void *)&expectedElement);

    TEST_ASSERT_EQUAL_INT(count, 1);
    TEST_ASSERT_EQUAL_INT(*expectedElement, 12);
}

void queueFront_returnsFalseForEmptyQueue() {
    int *element;

    TEST_ASSERT_FALSE(queueFront(queue, (void *)&element));
}

void queueFront_returnsTrueForNonEmptyQueue() {
    int *expectedElement;
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    enqueue(queue, element);

    TEST_ASSERT_TRUE(queueFront(queue, (void *)&expectedElement));
}

void queueFront_returnsFrontElement() {
    int *actualElement1;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    int *element3 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;
    *element3 = 3;

    enqueue(queue, element1);
    enqueue(queue, element2);
    enqueue(queue, element3);
    queueFront(queue, (void *)&actualElement1);

    TEST_ASSERT_EQUAL_INT(*actualElement1, 1);
}

void queueFront_doesNotRemoveElementsFromQueue() {
    int *actualElement1;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    int *element3 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;
    *element3 = 3;

    enqueue(queue, element1);
    enqueue(queue, element2);
    enqueue(queue, element3);
    queueFront(queue, (void *)&actualElement1);

    TEST_ASSERT_EQUAL_INT(queueCount(queue), 3);
}

void queueRear_returnsFalseForEmptyQueue() {
    int *element;

    TEST_ASSERT_FALSE(queueRear(queue, (void *)&element));
}

void queueRear_returnsTrueForNonEmptyQueue() {
    int *expectedElement;
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    enqueue(queue, element);

    TEST_ASSERT_TRUE(queueRear(queue, (void *)&expectedElement));
}

void queueRear_returnsRearElement() {
    int *actualElement1;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    int *element3 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;
    *element3 = 3;

    enqueue(queue, element1);
    enqueue(queue, element2);
    enqueue(queue, element3);
    queueRear(queue, (void *)&actualElement1);

    TEST_ASSERT_EQUAL_INT(*actualElement1, 3);
}

void queueRear_doesNotRemoveElementsFromQueue() {
    int *actualElement1;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    int *element3 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;
    *element3 = 3;

    enqueue(queue, element1);
    enqueue(queue, element2);
    enqueue(queue, element3);
    queueRear(queue, (void *)&actualElement1);

    TEST_ASSERT_EQUAL_INT(queueCount(queue), 3);
}

void fullQueue_returnsFalseIfMemoryCanBeAllocated() {
    TEST_ASSERT_FALSE(fullQueue(queue));
}

void dequeue_returnsElementsInFifoOrder() {
    int *actualElement1;
    int *actualElement2;
    int *actualElement3;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    int *element3 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;
    *element3 = 3;

    enqueue(queue, element1);
    enqueue(queue, element2);
    enqueue(queue, element3);
    dequeue(queue, (void *)&actualElement1);
    dequeue(queue, (void *)&actualElement2);
    dequeue(queue, (void *)&actualElement3);

    TEST_ASSERT_EQUAL_INT(*actualElement1, 1);
    TEST_ASSERT_EQUAL_INT(*actualElement2, 2);
    TEST_ASSERT_EQUAL_INT(*actualElement3, 3);
}