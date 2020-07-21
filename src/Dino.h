//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"

#define JUMP_TIME 16.6f
#define JUMP_FORCE 19.f

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    void draw() override;

    void clean() override;

    void update(float delta) override;

    void initLife() override {
        for (int i = 0; i <= 3; i++)
            life.push(i);
    }

    void loseLife() override {
        if (!life.empty() && life.top() != 0)
            life.pop();
    }

    std::stack<int> getLife() override {
        return life;
    }

private:
    Animation *animation;
    RigidBody *rigidBody;

    bool isJumping{};
    bool isOnGround{};

    float jumpTime;
    float jumpForce;

    Collider *collider;
    Vector2D lastPosition;

    std::stack<int> life;
};


#endif //Dino_H
