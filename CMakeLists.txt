cmake_minimum_required(VERSION 3.30)
project(pacman)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.0)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(pacmanClient client/Main.cpp)

target_sources(pacmanClient PRIVATE
        client/GameConfig.h
        client/Game.cpp
)

target_link_libraries(pacmanClient sfml-graphics sfml-window sfml-system)

add_executable(pacmanServer server/Server.cpp)
