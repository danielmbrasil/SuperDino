//
// Created by daniel on 17/07/2020.
//

#ifndef INC_2D_SUPERDINO_STATEMANAGER_H
#define INC_2D_SUPERDINO_STATEMANAGER_H

#include <stack>
#include "GameState.h"

class GameState;

class StateManager {
public:
    StateManager() = default;
    ~StateManager() = default;

    void addState(GameState *state);
    void popState();
    void update(float dt);
    void render();
    bool isEmpty();

private:
    std::stack<GameState *> m_States;
};


#endif //INC_2D_SUPERDINO_STATEMANAGER_H
