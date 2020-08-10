//
// Created by Daniel M Brasil on 8/10/20.
//

#ifndef Coins_H
#define Coins_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"

class Collider;

class Coins : public Character {
public:
    explicit Coins(Properties *properties);

    ~Coins();

    void draw() override;

    void clean() override;

    void update(float delta) override;

    SDL_Rect getCollider();

private:
    Animation *animation;

    Collider *collider;
};


#endif //Coins_H
