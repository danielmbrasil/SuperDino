//
// Created by daniel on 17/07/2020.
//

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "GameObject.h"
#include "Camera.h"
#include "UILabel.h"
#include "GameMap.h"
#include "DinoEnemy.h"
#include "Dino.h"
#include <vector>
#include "Coins.h"

class Dino;

class UILabel;

class DinoEnemy;

class Coins;

class PlayState : public GameState {
public:
    PlayState(float x, float y, int l, int c, int score);

    ~PlayState();

    void render() override;

    void update(float dt) override;

    void clear();

    inline GameMap *getMap() { return levelMap_1; }

    int getDinoLife();

    //inline DinoEnemy *getEnemy() { return enemy;}

    void enemyDeath(int index);

    inline std::vector<DinoEnemy *> getEnemies() { return enemies; }

    void enemySuicide(DinoEnemy *e);

    inline std::vector<Coins *> getCoins() { return coins; }

    void eraseCoin(int index);

    int getCollectedCoins();

    int getScore();

private:
    UILabel *lifeLabel;
    UILabel *pointsLabel;
    UILabel *scoreLabel;

    Dino *dino;
    GameMap *levelMap_1;

    std::vector<DinoEnemy *> enemies;
    std::vector<Coins *> coins;
};


#endif //PLAYSTATE_H
