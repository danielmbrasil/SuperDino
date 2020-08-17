//
// Created by Daniel M Brasil on 8/15/20.
//

#include "GameOverState.h"
#include "KeyboardController.h"
#include "TextureManager.h"

GameOverState::GameOverState(int life, int coins, int sc) {
    m_Context = Game::getInstance()->getRenderer();

    finalLife = life;
    collectedCoins = coins;
    score = sc;

    if (finalLife == 0) {
        v_labels.push_back(new UILabel(400, 10, "GAME OVER", "minecraft", yellow));
    } else {
        v_labels.push_back(new UILabel(400, 10, "YOU WON", "minecraft", yellow));
    }

    v_labels.push_back(new UILabel(120, 200, "x" + std::to_string(finalLife), "minecraftBigger", white));
    v_labels.push_back(new UILabel(460, 200, std::to_string(collectedCoins), "minecraftBigger", white));
    v_labels.push_back(new UILabel(780, 200, std::to_string(score), "minecraftBigger", white));

    // set labels position
    position[0].x = 50;
    position[0].y = 300;
    position[1].x = 320;
    position[1].y = 300;
    position[2].x = 780;
    position[2].y = 300;

    // reload textures
    TextureManager::getInstance()->loadTexture("background", "../assets/images/background.png");
    TextureManager::getInstance()->loadTexture("dino_idle", "../assets/images/dino_idle.png");
    TextureManager::getInstance()->loadTexture("coins", "../assets/images/coin32.png");

    // create new labels
    for (int i = 0; i < 3; i++)
        labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", white);
}

GameOverState::~GameOverState() {
    for (auto &v : v_labels)
        delete v;
}

void GameOverState::events() {
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
                TextureManager::getInstance()->drop("dino_idle");
                TextureManager::getInstance()->drop("coins");
                TextureManager::getInstance()->drop("background");
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->unsetGameOverState();
                Game::getInstance()->startGame();
                SDL_Delay(300);
            } else if (KeyboardController::getInstance()->getMouseButtonDown() && i == 1) {
                for (auto &label : labels)
                    label->clean();
                TextureManager::getInstance()->drop("dino_idle");
                TextureManager::getInstance()->drop("coins");
                TextureManager::getInstance()->drop("background");
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->unsetGameOverState();
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

void GameOverState::update(float dt) {

}

void GameOverState::render() {
    SDL_SetRenderDrawColor(m_Context, 0, 0, 0, 0);
    SDL_RenderClear(m_Context);

    TextureManager::getInstance()->draw("background", 0, 0, 900, 480);

    for (auto &v : v_labels)
        v->draw();
    
    TextureManager::getInstance()->drawFrame("dino_idle", (int) (70.f + Camera::getInstance()->getPosition().x), 185,
                                             24, 24, 0, 0, 2);
    TextureManager::getInstance()->drawFrame("coins", (int) (415.f + Camera::getInstance()->getPosition().x), 195,
                                             32, 32, 0, 0, 1);

    for (auto &label : labels)
        label->draw();

    SDL_RenderPresent(m_Context);
}
