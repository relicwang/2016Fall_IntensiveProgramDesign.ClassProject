cmake_minimum_required(VERSION 3.3)
project(lecture CXX)
include(.ipd/CMakeLists.txt)




add_test_program(fibonacci_heap_test
        test/fibo_test.cpp
        src/FibonacciHeap.h

        )