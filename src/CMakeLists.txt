cmake_minimum_required(VERSION 3.13)
project(c_data_structures C)

set(CMAKE_C_STANDARD 99)
set(TARGET_GROUP production CACHE STRING "Group to build")

add_subdirectory(dataStructures)

if(TARGET_GROUP STREQUAL production)
    add_subdirectory(main)
elseif(TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory(unity)
    add_subdirectory(test)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()