//
// Created by daniel on 17/07/2020.
//

#include "PlayState.h"
#include "MapParser.h"
#include "Collision.h"
#include <sstream>
#include <algorithm>

PlayState::PlayState(float x, float y, int l) {
    // get renderer context
    m_Context = Game::getInstance()->getRenderer();

    // load level 1 map
    levelMap_1 = MapParser::getInstance()->getMaps("MAP");
    TextureManager::getInstance()->parseTexture("../assets/textures.xml");

    // create Dino
    dino = new Dino(new Properties("dino", x, y, 24, 24));
    dino->setLife(l);

    // create camera
    Camera::getInstance()->setTarget(dino->getOrigin());

    // create dino enemies
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1000.f, 290.f, 24, 24)));
    enemies.push_back(new DinoEnemy(new Properties("dino_enemy", 1350.f, 290.f, 24, 24)));

    //create lifeLabel
    SDL_Color yellow = {248, 160, 0};
    lifeLabel = new UILabel(10, 10, "Dino", "minecraft", yellow);
}

PlayState::~PlayState() = default;

void PlayState::render() {
    //SDL_SetRenderDrawColor(m_Context, 91, 110, 225, 255);
    SDL_RenderClear(m_Context);

    levelMap_1->render();

    for (auto &e : enemies)
        e->draw();

    dino->draw();
    lifeLabel->draw();

    SDL_Rect camera = Camera::getInstance()->getViewBox();

    SDL_RenderCopy(m_Context, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Context);
}

void PlayState::update(float dt) {
    std::stringstream ss;
    ss << "Dino x" << dino->getLife();
    lifeLabel->clean();
    lifeLabel->setLabelText(ss.str(), "minecraft");

    Camera::getInstance()->update();

    levelMap_1->update();
    dino->update(dt);
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

    delete lifeLabel;
    delete dino;
    delete enemy;
}

void PlayState::enemyDeath(int index) {
    enemies.erase(enemies.begin() + index);
}

void PlayState::enemySuicide(DinoEnemy *e) {
    auto it = std::find(enemies.begin(), enemies.end(), e);
    enemies.erase(it);
}
