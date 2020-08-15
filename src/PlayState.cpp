//
// Created by daniel on 17/07/2020.
//

#include "PlayState.h"
#include "MapParser.h"
#include "Collision.h"
#include <sstream>
#include <algorithm>

PlayState::PlayState(float x, float y, int l, int c) {
    // get renderer context
    m_Context = Game::getInstance()->getRenderer();

    // load level 1 map
    levelMap_1 = MapParser::getInstance()->getMaps("MAP");
    TextureManager::getInstance()->parseTexture("../assets/textures.xml");

    // create Dino
    dino = new Dino(new Properties("dino", x, y, 24, 24));
    dino->setLife(l);
    dino->setCoins(c);

    // create camera
    Camera::getInstance()->setTarget(dino->getOrigin());

    // create dino enemies
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1000.f, 290.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1350.f, 290.f, 24, 24)));

    // create coins
    coins.push_back(new Coins(new Properties("coins", 320.f, 160.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 352.f, 160.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1024.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1056.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1088.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1120.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1152.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1184.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 1216.f, 164.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 2272.f, 128.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 3776.f, 96.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 4800.f, 96.f, 32, 32)));
    coins.push_back(new Coins(new Properties("coins", 5632.f, 256.f, 32, 32)));

    //create lifeLabel
    SDL_Color yellow = {248, 160, 0};
    lifeLabel = new UILabel(10, 10, "Dino", "minecraft", yellow);

    pointsLabel = new UILabel(450, 10, "X0", "minecraft", yellow);
}

PlayState::~PlayState() = default;

void PlayState::render() {
    //SDL_SetRenderDrawColor(m_Context, 91, 110, 225, 255);
    SDL_RenderClear(m_Context);

    levelMap_1->render();
    TextureManager::getInstance()->draw("coins", (int) (420.f + Camera::getInstance()->getPosition().x), 5, 32, 32,
                                        SDL_FLIP_NONE, 0.6f);
    for (auto &e : enemies)
        e->draw();

    dino->draw();
    lifeLabel->draw();
    pointsLabel->draw();

    for (auto &c : coins)
        c->draw();

    SDL_Rect camera = Camera::getInstance()->getViewBox();

    SDL_RenderCopy(m_Context, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Context);
}

void PlayState::update(float dt) {
    std::stringstream lifeStream;
    lifeStream << "Dino x" << dino->getLife();
    lifeLabel->clean();
    lifeLabel->setLabelText(lifeStream.str(), "minecraft");

    std::stringstream pointsStream;
    pointsStream << "X" << dino->getCoinsCollected();
    pointsLabel->clean();
    pointsLabel->setLabelText(pointsStream.str(), "minecraft");
    Camera::getInstance()->update();

    levelMap_1->update();
    dino->update(dt);

    for (auto &c : coins)
        c->update(dt);

    for (auto &e : enemies) {
        e->update(dt);

        SDL_Rect dinoRect, enemyRect;

        dinoRect = dino->getCollider();
        enemyRect = e->getCollider();

        if (Collision::getInstance()->checkCollision(dinoRect, enemyRect) && !dino->getDinoHitFirst()) {
            dino->loseLife();
            SDL_Delay(500);
            Game::getInstance()->newVoidState(dino->getLife());
        }
    }
}

int PlayState::getDinoLife() {
    return dino->getLife();
}

void PlayState::clear() {
    dino->clean();
    for (auto &e : enemies)
        e->clean();

    lifeLabel->clean();
    pointsLabel->clean();

    for (auto &c : coins)
        c->clean();

    delete lifeLabel;
    delete pointsLabel;

    delete dino;

    for (auto &c : coins)
        delete c;
}

void PlayState::enemyDeath(int index) {
    enemies.erase(enemies.begin() + index);
}

void PlayState::enemySuicide(DinoEnemy *e) {
    auto it = std::find(enemies.begin(), enemies.end(), e);
    enemies.erase(it);
}

void PlayState::eraseCoin(int index) {
    coins.erase(coins.begin() + index);
}

int PlayState::getCollectedCoins() {
    return dino->getCoinsCollected();
}
