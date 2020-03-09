add_library(dataStructures STATIC heap.c heap.h list.c list.h queue.c queue.h stack.c stack.h tree.c tree.h)

target_include_directories(dataStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})