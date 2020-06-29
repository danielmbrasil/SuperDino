//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    void draw() override;
    void clean() override;
    void update(float delta) override;

private:
    int m_Row, m_Frame{}, m_FrameCount;
    int animSpeed;
};


#endif //Dino_H
