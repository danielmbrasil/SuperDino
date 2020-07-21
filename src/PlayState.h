//
// Created by daniel on 17/07/2020.
//

#ifndef INC_2D_SUPERDINO_PLAYSTATE_H
#define INC_2D_SUPERDINO_PLAYSTATE_H

#include "GameState.h"
#include "GameObject.h"
#include "Camera.h"
#include "UILabel.h"
#include "GameMap.h"

class UILabel;

class PlayState : public GameState {
public:
    PlayState(float x, float y);

    void render() override;

    void update(float dt) override;

    void clear();

    inline GameMap *getMap() { return levelMap_1; }

    inline int getDinoLife() { return dino->getLife().top(); }

private:
    UILabel *lifeLabel;
    GameObject *dino;
    GameMap *levelMap_1;
};


#endif //INC_2D_SUPERDINO_PLAYSTATE_H
