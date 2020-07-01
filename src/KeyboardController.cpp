//
// Created by Daniel M Brasil on 6/29/20.
//

#include "KeyboardController.h"
#include "Game.h"

KeyboardController* KeyboardController::s_Instance = nullptr;

KeyboardController::KeyboardController() {
    m_KeYStates = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));
}

void KeyboardController::listen() {
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Game::getInstance()->quit();
                break;
            case SDL_KEYDOWN:
                keyDown();
                break;
            case SDL_KEYUP:
                keyUp();
                break;
            default:
                break;
        }
    }
}

bool KeyboardController::getKeyDown(SDL_Scancode key) {
    return  m_KeYStates[key] == 1;
}


void KeyboardController::keyUp() {
    m_KeYStates = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));
}

void KeyboardController::keyDown() {

}
