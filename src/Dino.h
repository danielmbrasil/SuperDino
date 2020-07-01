//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    void draw() override;
    void clean() override;
    void update(float delta) override;

private:
    Animation *animation;
    RigidBody *rigidBody;
};


#endif //Dino_H
