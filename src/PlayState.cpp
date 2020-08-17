//
// Created by daniel on 17/07/2020.
//

#include "PlayState.h"
#include "MapParser.h"
#include "Collision.h"
#include <sstream>
#include <algorithm>

PlayState::PlayState(float x, float y, int l, int c, int score) {
    // get renderer context
    m_Context = Game::getInstance()->getRenderer();

    // load level 1 map
    levelMap_1 = MapParser::getInstance()->getMaps("MAP");
    TextureManager::getInstance()->parseTexture("../assets/textures.xml");

    // create Dino
    dino = new Dino(new Properties("dino", x, y, 24, 24));
    dino->setLife(l);
    dino->setCoins(c);
    dino->setScore(score);

    // create camera
    Camera::getInstance()->setTarget(dino->getOrigin());

    // create dino enemies
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 608.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 640.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 1504.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1888.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1920.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 2000.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 2688.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 3584.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 3616.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 3648.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 3680.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 3712.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 5568.f, 340.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy_blue", 5600.f, 340.f, 24, 24)));

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

    // create cactus
    cactus.push_back(new Cactus(new Properties("cactus", 608.f, 312.f, 48, 48)));
    cactus.push_back(new Cactus(new Properties("cactus", 1600.f, 312.f, 48, 48)));
    cactus.push_back(new Cactus(new Properties("cactus", 3168.f, 248.f, 48, 48)));
    cactus.push_back(new Cactus(new Properties("cactus", 4448.f, 312.f, 48, 48)));
    cactus.push_back(new Cactus(new Properties("cactus", 5888.f, 312.f, 48, 48)));

    //create lifeLabel
    SDL_Color yellow = {248, 160, 0};
    lifeLabel = new UILabel(10, 10, "Dino", "minecraft", yellow);

    pointsLabel = new UILabel(450, 10, "X0", "minecraft", yellow);

    scoreLabel = new UILabel(780, 10, "SCORE: 0" , "minecraft", yellow);
}

PlayState::~PlayState() {
    for (auto &e : enemies)
        delete e;

    for (auto &c : coins)
        delete c;

    for (auto &c : cactus)
        delete c;

    delete lifeLabel;
    delete pointsLabel;
    delete scoreLabel;
    delete dino;
}

void PlayState::render() {
    //SDL_SetRenderDrawColor(m_Context, 91, 110, 225, 255);
    SDL_RenderClear(m_Context);

    levelMap_1->render();
    TextureManager::getInstance()->draw("coins", (int) (420.f + Camera::getInstance()->getPosition().x), 5, 32, 32,
                                        SDL_FLIP_NONE, 0.6f);

    for (auto &e : enemies)
        e->draw();

    for (auto &c : cactus)
        c->draw();

    dino->draw();
    lifeLabel->draw();
    pointsLabel->draw();
    scoreLabel->draw();

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

    std::stringstream scoreStream;
    scoreStream << "SCORE: " << dino->getScore();
    scoreLabel->clean();
    scoreLabel->setLabelText(scoreStream.str(), "minecraft");

    Camera::getInstance()->update();
    levelMap_1->update();
    dino->update(dt);

    for (auto &c : coins)
        c->update(dt);

    for (auto &c : cactus) {
        c->update(dt);

        SDL_Rect dinoRect, cactusRect;

        dinoRect = dino->getCollider();
        cactusRect = c->getCollider();

        if (Collision::getInstance()->checkCollision(dinoRect, cactusRect)) {
            dino->loseLife();
            SDL_Delay(500);
            Game::getInstance()->newVoidState(dino->getLife());
        }
    }

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

    if (dino->getLife() == 0 || dino->getCollider().x > 6176) {
        Game::getInstance()->getManager()->popState();
        clear();
        Game::getInstance()->unsetPlayState();
        Game::getInstance()->newGameOverState(dino->getLife(), dino->getCoinsCollected(), dino->getScore());
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
    scoreLabel->clean();

    for (auto &c : coins)
        c->clean();

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

int PlayState::getScore() {
    return dino->getScore();
}
