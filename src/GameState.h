//
// Created by daniel on 17/07/2020.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StateManager.h"
#include <SDL2/SDL.h>

class StateManager;

class GameState {
public:
    GameState();

    virtual ~GameState();

    virtual void update(float dt) = 0;

    virtual void render() = 0;

    void setManager(StateManager *m);

private:
    StateManager *manager;

protected:
    SDL_Renderer *m_Context{};
};


#endif //GAMESTATE_H
