cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

project(bomberman LANGUAGES CXX)

include_directories(include)

find_package(raylib 3.8 QUIET)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/3.7.0.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

if (WIN32)
        file(COPY ./assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()


# add the executable
add_executable(bomberman
        src/game/main.cpp
        src/game/bomb_management.cpp
        src/game/bonus_management.cpp
        src/game/asset_loading.cpp
        src/game/draw.cpp
        src/raylib/window/window.cpp
        src/raylib/window/window.h
        src/raylib/myRaylib.h
        src/raylib/audio/audio.cpp
        src/raylib/audio/audio.h
        src/raylib/events/event.cpp
        src/raylib/events/event.h
        src/raylib/graphics/graphics.cpp
        src/raylib/graphics/graphics.hpp
        src/game/Engine/Engine.cpp
        src/game/Engine/Engine.h
        src/game/Engine/Bomb_Engine/Bomb.cpp
        src/game/Engine/Bomb_Engine/Bomb.hpp
        include/game.h
        src/game/Engine/Object/Block.cpp
        src/game/Engine/Object/Block.h
        src/game/Engine/Map/GameMap.cpp
        src/game/Engine/Map/GameMap.h
        include/prototypes.h
        src/raylib/graphics/Model/Model.cpp
        src/raylib/graphics/Model/Model.h
        src/game/Engine/Player/APlayer.cpp
        src/game/Engine/Player/APlayer.h
        src/raylib/graphics/Model/AModel.cpp
        src/raylib/graphics/Model/AModel.h
        src/game/Engine/Player/Player.cpp
        src/game/Engine/Player/Player.hpp
        src/game/Engine/Player/AI.cpp
        src/game/Engine/Player/AI.h
        include/pl_mpeg.h
        src/game/Menu/Menu.cpp
        src/game/Menu/Menu.hpp
        include/PlayerNum.h
        include/Direction.h
        include/pl_mpeg.h
        include/rotationValues.h
        src/errors/Error.cpp
        src/errors/Error.h)

target_link_libraries(${PROJECT_NAME} raylib)
