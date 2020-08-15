//
// Created by daniel on 7/20/20.
//

#include "VoidState.h"
#include "Game.h"
#include <string>
#include "TextureManager.h"

VoidState::VoidState(int life, int coins, int sc) {
    m_Context = Game::getInstance()->getRenderer();
    currentLife = life;
    collectedCoins = coins;
    score = sc;

    label = new UILabel(450, 200, "X" + std::to_string(currentLife), "minecraftBigger", white);
    coinsLabel = new UILabel(450, 10, "X" + std::to_string(collectedCoins), "minecraft", white);
    scoreLabel = new UILabel(780, 10, "SCORE: " + std::to_string(score), "minecraft", white);
}

VoidState::~VoidState() {
    delete label;
    delete coinsLabel;
    delete scoreLabel;
}

void VoidState::update(float dt) {
    SDL_Delay(3000);

    label->clean();
    coinsLabel->clean();
    scoreLabel->clean();

    TextureManager::getInstance()->drop("dino_crying");
    Game::getInstance()->getManager()->popState();
    Game::getInstance()->getManager()->popState();
    Game::getInstance()->getPlayState()->clear();
    Game::getInstance()->unsetPlayState();
    Game::getInstance()->restartGame(currentLife, collectedCoins, score);
    Game::getInstance()->unsetVoidState();
}

void VoidState::render() {
    SDL_SetRenderDrawColor(m_Context, 0, 0, 0, 0);
    SDL_RenderClear(m_Context);

    TextureManager::getInstance()->drawFrame("dino_crying", (int) (400.f + Camera::getInstance()->getPosition().x), 190,
                                             24, 24, 0, 1, 2);
    label->draw();
    coinsLabel->draw();
    scoreLabel->draw();

    TextureManager::getInstance()->draw("coins", (int) (420.f + Camera::getInstance()->getPosition().x), 5, 32, 32,
                                        SDL_FLIP_NONE, 0.6f);
    SDL_RenderPresent(m_Context);
}
