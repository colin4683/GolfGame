cmake_minimum_required(VERSION 3.22)
# Project Name
project(GolfGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp Ball/Ball.cpp Ball/Ball.h Ball/Settings.h Rendering/Gadient.cpp Rendering/Gadient.h Game/Game.cpp Game/Game.h)
add_executable(GolfGame ${SOURCE_FILES})
include_directories(/opt/homebrew/Cellar/sfml/2.5.1_1/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(GolfGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)