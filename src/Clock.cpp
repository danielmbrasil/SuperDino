//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Clock.h"
#include <SDL2/SDL.h>

Clock* Clock::s_Instance = nullptr;

void Clock::tick() {
    deltaTime = (SDL_GetTicks() - lastTime) * (TARGET_FPS/1000.0f);

    if (deltaTime > TARGET_DELTATIME)
        deltaTime = TARGET_DELTATIME;

    lastTime = SDL_GetTicks();
}
