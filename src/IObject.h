//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef IObject_H
#define IObject_H


class IObject {
public:
    virtual void draw() = 0;

    virtual void update(float delta) = 0;

    virtual void clean() = 0;
};


#endif //IObject_H
