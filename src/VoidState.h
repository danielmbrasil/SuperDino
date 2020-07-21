//
// Created by daniel on 7/20/20.
//

#ifndef INC_2D_SUPERDINO_VOIDSTATE_H
#define INC_2D_SUPERDINO_VOIDSTATE_H

#include "GameState.h"
#include "UILabel.h"

class VoidState : public GameState {
public:
    VoidState(int life);

    ~VoidState() = default;

    void update(float dt) override;

    void render() override;

private:
    int currentLife;
    UILabel *label;
    SDL_Color white = {255, 255, 255, 255};
};


#endif //INC_2D_SUPERDINO_VOIDSTATE_H
