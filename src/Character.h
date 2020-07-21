//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Character_H
#define Character_H

#include <stack>
#include "GameObject.h"

class Character : public GameObject {
public:
    explicit Character(Properties *properties) : GameObject(properties) {}

    void draw() override = 0;

    void clean() override = 0;

    void update(float delta) override = 0;


protected:
    std::string name;
};


#endif //Character_H
