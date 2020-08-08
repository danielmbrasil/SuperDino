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

class Dino;

class UILabel;

class DinoEnemy;

class PlayState : public GameState {
public:
    PlayState(float x, float y, int l);

    ~PlayState();

    void render() override;

    void update(float dt) override;

    void clear();

    inline GameMap *getMap() { return levelMap_1; }

    int getDinoLife();

    inline DinoEnemy *getEnemy() { return enemy;}

private:
    UILabel *lifeLabel;
    Dino *dino;
    DinoEnemy *enemy;
    GameMap *levelMap_1;
};


#endif //PLAYSTATE_H
