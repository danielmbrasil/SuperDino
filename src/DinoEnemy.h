//
// Created by daniel on 7/26/20.
//

#ifndef DINOENEMY_H
#define DINOENEMY_H

#include "Character.h"
#include "Animation.h"
#include "Collider.h"
#include "RigidBody.h"

class Collider;

class DinoEnemy : public Character {
public:
    explicit DinoEnemy(Properties *properties);

    ~DinoEnemy() override;

    void draw() override;

    void clean() override;

    void update(float delta) override;

    SDL_Rect getCollider();

    SDL_Rect getHeadCollider();

    void suicide();

private:
    Animation *animation;
    RigidBody *rigidBody;

    bool isForward;
    float initialPosition;

    Collider *collider;
    Collider *head;
    Vector2D lastPosition;
};


#endif //DINOENEMY_H
