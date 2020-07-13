//
// Created by daniel on 12/07/2020.
//

#ifndef INC_2D_SUPERDINO_HPBAR_H
#define INC_2D_SUPERDINO_HPBAR_H

#include "Game.h"

class HPBar {
public:
    static void RenderHPBar(int x, int y, int w, int h,  SDL_Color FGColor, SDL_Color BGColor);

    static SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    static void update(float life_Status) {
        HPBar::lifeStatus = life_Status;
    }

private:
    static float lifeStatus;
};

#endif //INC_2D_SUPERDINO_HPBAR_H
