//
// Created by daniel on 17/07/2020.
//

#ifndef INC_2D_SUPERDINO_MENUSTATE_H
#define INC_2D_SUPERDINO_MENUSTATE_H

#include "GameState.h"
#include <SDL2/SDL.h>

class MenuState : public GameState {
public:
    MenuState();
    void update(float dt) override;

    void render() override;

};


#endif //INC_2D_SUPERDINO_MENUSTATE_H
