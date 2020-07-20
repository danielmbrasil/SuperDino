//
// Created by Daniel M Brasil on 6/28/20.
//

#ifndef Layer_H
#define Layer_H


class Layer {
public:
    virtual void render() = 0;

    virtual void update() = 0;
};


#endif //Layer_H
