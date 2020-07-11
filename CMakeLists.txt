cmake_minimum_required(VERSION 3.16)
project(2D_SuperDino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(2D_SuperDino
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TextureManager.cpp
        src/TextureManager.h
        src/Vector2D.cpp
        src/Vector2D.h
        src/RigidBody.h
        src/Layer.h
        src/GameMap.h
        src/TileLayer.cpp
        src/TileLayer.h
        src/MapParser.cpp
        src/MapParser.h
        vendor/tinyxml/tinystr.h
        vendor/tinyxml/tinystr.cpp
        vendor/tinyxml/tinyxml.h
        vendor/tinyxml/tinyxml.cpp
        vendor/tinyxml/tinyxmlerror.cpp
        vendor/tinyxml/tinyxmlparser.cpp
        src/IObject.h
        src/GameObject.h
        src/Transform.h
        src/Character.h
        src/Dino.cpp
        src/Dino.h
        src/Animation.cpp
        src/Animation.h
        src/KeyboardController.cpp
        src/KeyboardController.h
        src/Clock.cpp
        src/Clock.h
        src/Camera.cpp
        src/Camera.h
        src/Collision.cpp
        src/Collision.h
        src/Collider.h
        src/FontManager.cpp
        src/FontManager.h
        src/UILabel.h src/UILabel.cpp)

target_link_libraries(2D_SuperDino -lSDL2 -lSDL2_image -lSDL2_ttf)