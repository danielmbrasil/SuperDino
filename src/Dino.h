//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include <stack>

#define JUMP_TIME 20.0f
#define JUMP_FORCE 11.0f

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    void draw() override;
    void clean() override;
    void update(float delta) override;

    void initLife() {
        for (int i = 0; i <= 30; i++)
            dinoLife.push((float) i);
    }

    void loseLife() {
        if(!dinoLife.empty() && dinoLife.top() != 0.f)
            dinoLife.pop();
    }

    std::stack<float> getLife() { return dinoLife; }

private:
    Animation *animation;
    RigidBody *rigidBody;

    bool isJumping{};
    bool isOnGround{};

    float jumpTime;
    float jumpForce;

    Collider *collider;
    Vector2D lastPosition;

    std::stack<float> dinoLife;
};


#endif //Dino_H
