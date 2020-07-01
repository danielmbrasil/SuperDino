//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Transform_H
#define Transform_H

#include "Vector2D.h"

class Transform {
public:
    float x, y;

    explicit Transform(float x = 0.0f, float y = 0.0f) : x(x), y (y) {}

    inline void moveX(float X) { x += X;}
    inline void moveY(float Y) { y += Y; }
    inline void move(Vector2D &vec) {
        x += vec.x;
        y += vec.y;
    }
};


#endif //Transform_H
