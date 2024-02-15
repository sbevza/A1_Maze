cmake_minimum_required(VERSION 3.23)
project(A1_Maze_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets OpenGLWidgets REQUIRED)
find_package(GTest REQUIRED)

include_directories(src/Maze/controllers)
include_directories(src/Maze/models)
include_directories(src/Maze/views)

add_executable(A1_Maze_2
        src/Maze/main.cc
        src/Maze/views/cave.cc
        src/Maze/views/cave.h
        src/Maze/views/mainwindow.cc
        src/Maze/views/mainwindow.h
        src/Maze/maze.pro
        src/Maze/models/maze.cc
        src/Maze/models/maze.h
        src/Maze/controllers/maze_controller.cc
        src/Maze/controllers/maze_controller.h
        src/Maze/models/maze_solver.cc
        src/Maze/models/maze_solver.h
        src/Maze/models/maze_generator.cc
        src/Maze/models/maze_generator.h
        src/Maze/models/cave_model.cc
        src/Maze/models/cave_model.h
        src/Maze/controllers/cave_controller.cc
        src/Maze/controllers/cave_controller.h
)

target_link_libraries(A1_Maze_2 m Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets gtest gtest_main)

add_executable(A1_Maze_Tests
        src/Tests/maze_test.cc
        src/Tests/cave_test.cc
        src/Tests/maze_solver_test.cc
        src/Tests/maze_generator_test.cc
        src/Maze/models/maze.cc
        src/Maze/models/maze_solver.cc
        src/Maze/models/maze_generator.cc
        src/Maze/controllers/maze_controller.cc
        src/Maze/controllers/maze_controller.h
        src/Tests/test.cc
)

target_include_directories(A1_Maze_Tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(A1_Maze_Tests ${GTEST_LIBRARIES} Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets pthread)

enable_testing()
add_test(NAME maze_solver_test COMMAND A1_Maze_Tests)
