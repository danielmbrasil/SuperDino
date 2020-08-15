//
// Created by Daniel M Brasil on 6/30/20.
//

#include "Collision.h"
#include "PlayState.h"

Collision *Collision::s_Instance = nullptr;

Collision::Collision() {
    collision_layer = (TileLayer *) Game::getInstance()->getPlayState()->getMap()->getMapLayers().front();
    m_CollisionTileMap = collision_layer->getTileMap();
}

bool Collision::checkCollision(SDL_Rect &rectA, SDL_Rect &rectB) {
    return rectA.x + rectA.w >= rectB.x &&
           rectB.x + rectB.w >= rectA.x &&
           rectA.y + rectA.h >= rectB.y &&
           rectB.y + rectB.h >= rectA.y;
}

bool Collision::mapCollision(SDL_Rect rectA) {
    int tileSize = 32;
    int rows = 15;
    int columns = 200;

    int left_tile = rectA.x / tileSize;
    int right_tile = (rectA.x + rectA.w) / tileSize;

    int top_tile = rectA.y / tileSize;
    int bottom_tile = (rectA.y + rectA.h) / tileSize;

    if (left_tile < 0) left_tile = 0;
    if (right_tile > columns) right_tile = columns;

    if (top_tile < 0) top_tile = 0;
    if (bottom_tile > rows) bottom_tile = rows;

    for (int y = left_tile; y <= right_tile; y++)
        for (int x = top_tile; x <= bottom_tile; x++)
            if (m_CollisionTileMap[x][y] > 0)
                return true;

    return false;
}
