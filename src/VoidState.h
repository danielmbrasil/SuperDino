//
// Created by daniel on 7/20/20.
//

#ifndef VOIDSTATE_H
#define VOIDSTATE_H

#include "GameState.h"
#include "UILabel.h"

class VoidState : public GameState {
public:
    VoidState(int life);

    ~VoidState();

    void update(float dt) override;

    void render() override;

private:
    int currentLife;
    UILabel *label;
    SDL_Color white = {255, 255, 255, 255};
};


#endif //VOIDSTATE_H
