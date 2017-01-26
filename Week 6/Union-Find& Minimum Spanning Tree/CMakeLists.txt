cmake_minimum_required(VERSION 3.3)
project(mst CXX)
include(.ipd/CMakeLists.txt)

add_program(mst
        src/mst.h src/mst.cpp
        src/WU_graph.h src/WU_graph.cpp
        src/Union_find.h src/Union_find.cpp
        )


add_program(union_find_user_test
        src/Union_find_test.cpp
        src/Union_find.h
        src/Union_find.cpp
        )


add_test_program(graph_test
        test/graph_test.cpp src/WU_graph.h src/WU_graph.cpp)

add_test_program(uf_test
        test/uf_test.cpp src/Union_find.h src/Union_find.cpp)

add_test_program(mst_test
        test/mst_test.cpp
        src/mst.h src/mst.cpp
        src/WU_graph.h src/WU_graph.cpp
        src/Union_find.h src/Union_find.cpp)


add_test_program(mst_test2
        test/mst_test2.cpp
        src/mst.h src/mst.cpp
        src/WU_graph.h src/WU_graph.cpp
        src/Union_find.h src/Union_find.cpp)
