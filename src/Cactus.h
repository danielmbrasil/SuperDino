//
// Created by Daniel M Brasil on 16/08/2020.
//

#ifndef Cactus_H
#define Cactus_H

#include "Character.h"
#include "Collider.h"

class Cactus : public Character {
public:
    Cactus(Properties *properties);

    ~Cactus() override;

    void draw() override;

    void clean() override;

    void update(float delta) override;

    SDL_Rect getCollider();

private:
    Collider *collider;
};


#endif //Cactus_H
