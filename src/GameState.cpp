//
// Created by daniel on 17/07/2020.
//

#include "GameState.h"

GameState::GameState() {
    manager = nullptr;
}

void GameState::update(float dt) { }

void GameState::render() { }

StateManager *GameState::getManager() {
    return manager;
}

void GameState::setManager(StateManager *m) {
    manager = m;
}
