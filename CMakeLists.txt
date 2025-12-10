cmake_minimum_required(VERSION 3.10)
project(Figures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest REQUIRED)
include_directories(include)

add_executable(DND
    src/battle_visitor.cpp
    src/bear.cpp
    src/factory.cpp
    src/main.cpp
    src/npc.cpp
    src/orc.cpp
    src/squirrel.cpp
    src/world.cpp
)

add_executable(DND_test
    src/battle_visitor.cpp
    src/bear.cpp
    src/factory.cpp
    test/main.cpp
    test/dnd_test.cpp
    src/npc.cpp
    src/orc.cpp
    src/squirrel.cpp
    src/world.cpp
)


target_link_libraries(DND_test GTest::gtest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(DND_test)