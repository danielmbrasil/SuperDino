//
// Created by daniel on 17/07/2020.
//

#include "StateManager.h"

void StateManager::addState(GameState *state) {
    state->setManager(this);
    m_States.push(state);
}

void StateManager::popState() {
    m_States.pop();
}

void StateManager::update(float dt) {
    if (!m_States.empty())
        if (m_States.top() != nullptr)
            m_States.top()->update(dt);
}

void StateManager::render() {
    if (!m_States.empty())
        if(m_States.top() != nullptr)
            m_States.top()->render();
}

bool StateManager::isEmpty() {
    return m_States.empty();
}
