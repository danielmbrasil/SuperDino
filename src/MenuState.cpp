//
// Created by daniel on 17/07/2020.
//

#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() {
    m_Context = Game::getInstance()->getRenderer();
}

void MenuState::update(float dt) {
    GameState::update(dt);
}

void MenuState::render() {
    SDL_SetRenderDrawColor(m_Context, 255, 255, 255, 255);

    SDL_RenderClear(m_Context);
    SDL_RenderPresent(m_Context);
}
