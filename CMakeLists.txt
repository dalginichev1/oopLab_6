cmake_minimum_required(VERSION 3.10)
project(Figures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(DND
    src/BattleVisitor.cpp
    src/observer.cpp
    src/bear.cpp
    src/factory.cpp
    src/main.cpp
    src/npc.cpp
    src/orc.cpp
    src/squirrel.cpp
    src/world.cpp
)