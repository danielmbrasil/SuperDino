//
// Created by daniel on 12/07/2020.
//

#include "HPBar.h"
#include <iostream>

float HPBar::lifeStatus = 30.0f;

void HPBar::RenderHPBar(int x, int y, int w, int h, SDL_Color FGColor, SDL_Color BGColor) {
    float percent = (HPBar::lifeStatus / 10) / 3;
    percent = percent > 1.f ? 1.f : percent < 0.f ? 0.f : percent;
    //std::cout << percent << std::endl;
    SDL_Color old;
    SDL_GetRenderDrawColor(Game::getInstance()->getRenderer(), &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgrect = {x, y, w, h};
    SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(Game::getInstance()->getRenderer(), &bgrect);
    SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int) ((float) w * percent);
    int px = x + (w - pw);
    SDL_Rect fgrect = {px, y, pw, h};
    SDL_RenderFillRect(Game::getInstance()->getRenderer(), &fgrect);
    SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), old.r, old.g, old.b, old.a);
}

SDL_Color HPBar::color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color col = {r, g, b, a};
    return col;
}