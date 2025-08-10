cmake_minimum_required(VERSION 3.30)
project(pacman)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(pacmanClient client/main.cpp)

target_sources(pacmanClient PRIVATE
        client/MapConverter/MapConverter.hpp
        client/MapRenderer/MapRenderer.hpp
        client/TextRenderer/TextRenderer.hpp
        client/Ghost/Ghost.hpp
        client/Ghost/GhostManager.hpp
        client/Global.hpp
        client/MapCollision/MapCollision.hpp
        client/MapConverter/MapConverter.cpp
        client/MapRenderer/MapRenderer.cpp
        client/TextRenderer/TextRenderer.cpp
        client/Ghost/Ghost.cpp
        client/Ghost/GhostManager.cpp
        client/MapCollision/MapCollision.cpp
        client/Pacman/Pacman.hpp
        client/Pacman/Pacman.cpp
)

target_link_libraries(pacmanClient sfml-graphics sfml-window sfml-system sfml-audio)

#file(GLOB_RECURSE RESOURCES_FILES client/Resources/*)
#add_custom_command(
#        TARGET pacmanClient
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${RESOURCES_FILES}
#        $<TARGET_FILE_DIR:pacmanClient>/../client/Resources
#)

add_executable(pacmanServer server/Server.cpp)
