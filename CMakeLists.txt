cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenMP pour parallélisation
find_package(OpenMP REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

set(SOURCES
    src/Cell.cpp
    src/AliveCell.cpp
    src/DeadCell.cpp
    src/ObstacleCell.cpp
    src/ConwayRule.cpp
    src/Grid.cpp
    src/Game.cpp
    src/ConsoleView.cpp
    src/View.cpp
    src/GUIView.cpp
    src/FileManager.cpp
    src/PatternManager.cpp
)

add_executable(game_of_life ${SOURCES} src/main.cpp)
target_link_libraries(game_of_life 
    sfml-graphics sfml-window sfml-system 
    stdc++fs 
    OpenMP::OpenMP_CXX
)

add_executable(tests ${SOURCES} tests/tests.cpp)
target_link_libraries(tests 
    sfml-graphics sfml-window sfml-system 
    stdc++fs
    OpenMP::OpenMP_CXX
)

if(NOT MSVC)
    target_compile_options(game_of_life PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(tests PRIVATE -Wall -Wextra -pedantic)
endif()