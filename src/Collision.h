//
// Created by Daniel M Brasil on 6/30/20.
//

#ifndef Collision_H
#define Collision_H

#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Game.h"

class Collision {
public:
    static Collision *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Collision();
    }

    bool checkCollision(SDL_Rect &rectA, SDL_Rect &rectB);
    
    bool mapCollision(SDL_Rect rectA);

    bool cactusCollision(SDL_Rect rectA);

private:
    Collision();

    static Collision *s_Instance;
    TileMap m_CollisionTileMap;
    TileLayer *collision_layer;
    TileMap m_CactusCollision;
    TileLayer *cactus_layer;
};


#endif //Collision_H
