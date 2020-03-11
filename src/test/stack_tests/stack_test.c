#include <stdlib.h>
#include "unity.h"
#include "stack.h"

// Global test variables
static STACK *stack;

// test function prototypes
void createStack_createsEmptyStack();
void pushStack_addsElementToStack();
void popStack_removesElementFromStack();
void popStack_removesElementsFromStackInLifoOrder();
void popStack_returnsTopElement();
void popStack_returnsNullIfEmpty();
void stackTop_doesNotRemoveElementFromStack();
void stackTop_returnsTopElementValue();
void stackTop_returnsNullIfEmpty();
void fullStack_returnsFalseIfMemoryCanBeAllocated();

int main() {
    UNITY_BEGIN();
    RUN_TEST(createStack_createsEmptyStack);
    RUN_TEST(pushStack_addsElementToStack);
    RUN_TEST(popStack_removesElementFromStack);
    RUN_TEST(popStack_removesElementsFromStackInLifoOrder);
    RUN_TEST(popStack_returnsTopElement);
    RUN_TEST(stackTop_doesNotRemoveElementFromStack);
    RUN_TEST(stackTop_returnsTopElementValue);
    RUN_TEST(stackTop_returnsNullIfEmpty);
    RUN_TEST(popStack_returnsNullIfEmpty);
    RUN_TEST(fullStack_returnsFalseIfMemoryCanBeAllocated);

    return UNITY_END();
}

void setUp() {
    stack = createStack();
}
void tearDown() {
    destroyStack(stack);
}

void createStack_createsEmptyStack() {
    TEST_ASSERT_EQUAL_INT(stackCount(stack), 0);
    TEST_ASSERT_TRUE(emptyStack(stack));
}

void pushStack_addsElementToStack() {
    int *element = (int *)malloc(sizeof(int));
    *element = 12;

    pushStack(stack, element);

    TEST_ASSERT_EQUAL_INT(stack->count, 1);
}

void popStack_removesElementFromStack() {
    int *element = (int *)malloc(sizeof(int));
    *element = 19;

    pushStack(stack, element);
    popStack(stack);

    TEST_ASSERT_TRUE(emptyStack(stack));
}

void popStack_returnsTopElement() {
    int *actualElement;
    int *element = (int *)malloc(sizeof(int));
    *element = 19;

    pushStack(stack, element);
    actualElement = popStack(stack);

    TEST_ASSERT_EQUAL_INT(*actualElement, 19);
}

void popStack_removesElementsFromStackInLifoOrder() {
    int *actualElement1;
    int *actualElement2;
    int *element1 = (int *)malloc(sizeof(int));
    int *element2 = (int *)malloc(sizeof(int));
    *element1 = 1;
    *element2 = 2;

    pushStack(stack, element1);
    pushStack(stack, element2);
    actualElement1 = popStack(stack);
    actualElement2 = popStack(stack);

    TEST_ASSERT_EQUAL_INT(*actualElement1, 2);
    TEST_ASSERT_EQUAL_INT(*actualElement2, 1);
}

void popStack_returnsNullIfEmpty() {
    int *element;

    element = (int *)popStack(stack);

    TEST_ASSERT_NULL(element);
}

void stackTop_doesNotRemoveElementFromStack() {
    int *element = (int *)malloc(sizeof(int));
    *element = 19;

    pushStack(stack, element);
    stackTop(stack);

    TEST_ASSERT_EQUAL_INT(stackCount(stack), 1);
}

void stackTop_returnsTopElementValue() {
    int *actualElement;
    int *element = (int *)malloc(sizeof(int));
    *element = 19;

    pushStack(stack, element);
    actualElement = stackTop(stack);

    TEST_ASSERT_EQUAL_INT(*actualElement, 19);
}

void stackTop_returnsNullIfEmpty() {
    int *element;

    element = (int *)stackTop(stack);

    TEST_ASSERT_NULL(element);
}

void fullStack_returnsFalseIfMemoryCanBeAllocated() {
    TEST_ASSERT_FALSE(fullStack(stack));
}