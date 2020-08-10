//
// Created by daniel on 7/20/20.
//

#ifndef VOIDSTATE_H
#define VOIDSTATE_H

#include "GameState.h"
#include "UILabel.h"

class VoidState : public GameState {
public:
    VoidState(int life, int coins);

    ~VoidState();

    void update(float dt) override;

    void render() override;

private:
    int currentLife;
    int collectedCoins;

    UILabel *label;
    UILabel *coinsLabel;

    SDL_Color white = {255, 255, 255, 255};
};


#endif //VOIDSTATE_H
