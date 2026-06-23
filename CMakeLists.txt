cmake_minimum_required(VERSION 4.2)
project(CLion)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLion main.cpp
        dynamic_array.h
        linked_list.h)

add_executable(test_da test_dynamic_array.cpp
        dynamic_array.h)

add_executable(test_linked_list test_linked_list.cpp
        linked_list.h)

add_executable(test_stack test_stack.cpp
        stack.h)

add_executable(test_queue test_queue.cpp
        queue.h)

add_executable(test_doubly_linked_list test_doubly_linked_list.cpp
        doubly_linked_list.h)

add_executable(test_hash_table test_hash_table.cpp
        hash_table.h)

add_executable(test_bst test_bst.cpp
        bst.h)

add_executable(test_heap test_heap.cpp
        heap.h)

add_executable(test_graph test_graph.cpp
        graph.h)
