//
// Created by daniel on 17/07/2020.
//

#ifndef INC_2D_SUPERDINO_GAMESTATE_H
#define INC_2D_SUPERDINO_GAMESTATE_H

#include "StateManager.h"
#include <SDL2/SDL.h>

class StateManager;

class GameState {
public:
    GameState();

    ~GameState() = default;

    virtual void update(float dt) = 0;

    virtual void render() = 0;

    void setManager(StateManager *m);

private:
    StateManager *manager;

protected:
    SDL_Renderer *m_Context{};
};


#endif //INC_2D_SUPERDINO_GAMESTATE_H
