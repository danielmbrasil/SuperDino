//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"

#define JUMP_TIME 20.0f
#define JUMP_FORCE 11.0f

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    void draw() override;
    void clean() override;
    void update(float delta) override;

private:
    Animation *animation;
    RigidBody *rigidBody;

    bool isJumping{};
    bool isOnGround{};

    float jumpTime;
    float jumpForce;

    Collider *collider;
    Vector2D lastPosition;
};


#endif //Dino_H
