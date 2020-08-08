//
// Created by daniel on 7/19/20.
//

#include "PauseState.h"
#include "Game.h"
#include "KeyboardController.h"

PauseState::PauseState() {
    // get context
    m_Context = Game::getInstance()->getRenderer();

    // set labels position
    position[0].x = 100;
    position[0].y = 220;
    position[1].x = 100;
    position[1].y = 280;
    position[2].x = 100;
    position[2].y = 340;

    // create new labels
    for (int i = 0; i < 3; i++)
        labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", white);
}

PauseState::~PauseState() = default;

void PauseState::update(float dt) {

}

void PauseState::events() {
    int x = KeyboardController::getInstance()->getX();
    int y = KeyboardController::getInstance()->getY();

    for (int i = 0; i < 3; ++i) {
        if (x >= labels[i]->getPosition().x &&
            x <= labels[i]->getPosition().x + labels[i]->getPosition().w &&
            y >= labels[i]->getPosition().y &&
            y <= labels[i]->getPosition().y + labels[i]->getPosition().h) {
            labels[i]->clean();
            delete labels[i];
            labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", green);

            if (KeyboardController::getInstance()->getMouseButtonDown() && i == 0) {
                for (auto &label : labels)
                    label->clean();
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->unsetPause();
                SDL_Delay(300);
            } else if (KeyboardController::getInstance()->getMouseButtonDown() && i == 1) {
                for (auto &label : labels)
                    label->clean();
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->unsetPause();
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->getPlayState()->clear();
                Game::getInstance()->unsetPlayState();
                Game::getInstance()->newMenu();
                SDL_Delay(300);
            } else if (KeyboardController::getInstance()->getMouseButtonDown() && i == 2) {
                for (auto &label : labels) 
                    label->clean();
                Game::getInstance()->quit();
            }
        } else {
            labels[i]->clean();
            delete labels[i];
            labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", white);
        }
    }
}

void PauseState::render() {
    SDL_SetRenderDrawColor(m_Context, 0, 0, 0, 0);
    SDL_RenderClear(m_Context);

    for (auto &label : labels)
        label->draw();

    SDL_RenderPresent(m_Context);
}
