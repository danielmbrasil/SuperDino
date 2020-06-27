cmake_minimum_required(VERSION 3.16)
project(2D_SuperDino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(2D_SuperDino
        src/main.cpp
        src/AssetManager.cpp
        src/AssetManager.h
        src/Collision.cpp
        src/Collision.h
        src/Game.cpp
        src/Game.h
        src/TextureManager.cpp
        src/TextureManager.h
        src/Vector2D.cpp
        src/Vector2D.h
        src/ECS/ECS.h
        src/ECS/ECS.cpp
        src/ECS/Animation.h
        src/ECS/ColliderComponent.h
        src/ECS/Components.h
        src/ECS/KeyboardController.h
        src/ECS/SpriteComponent.h
        src/ECS/TileComponent.h
        src/ECS/TransformComponent.h)

target_link_libraries(2D_SuperDino -lSDL2 -lSDL2_image)