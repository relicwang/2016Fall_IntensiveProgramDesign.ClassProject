cmake_minimum_required(VERSION 3.3)
project(hexapawn CXX)
include(.ipd/CMakeLists.txt)

add_program(hexapawn
        src/hexapawn.cpp
        src/hexapawn.h)

add_program(vectorTest
        src/vectorTest.cpp
     )

add_test_program(hexapawn_test
        src/hexapawn.cpp
        src/hexapawn.h
        test/hexapawn_test.cpp
        )

add_program(hexapawn_main
        src/hexapawn_main.cpp
        src/hexapawn.h
        src/hexapawn.cpp)


add_program(string_test
        src/string_test.cpp
        )

