//
// Created by daniel on 7/20/20.
//

#include "VoidState.h"
#include "Game.h"
#include <string>

VoidState::VoidState(int life) {
    m_Context = Game::getInstance()->getRenderer();
    currentLife = life;

    label = new UILabel(400, 200, "X" + std::to_string(currentLife), "minecraftBigger", white);

}

void VoidState::update(float dt) {
    SDL_Delay(3000);
    label->clean();
    delete label;
    Game::getInstance()->getManager()->popState();
}

void VoidState::render() {
    SDL_SetRenderDrawColor(m_Context, 0, 0, 0, 0);
    SDL_RenderClear(m_Context);

    label->draw();

    SDL_RenderPresent(m_Context);
}
