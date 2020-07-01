//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef KeyboardController_H
#define KeyboardController_H

#include <SDL2/SDL.h>

class KeyboardController {
public:
    static KeyboardController* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new KeyboardController();
    }

    void listen();
    bool getKeyDown(SDL_Scancode key);

private:
    KeyboardController();
    static KeyboardController *s_Instance;

    SDL_Event event;
    Uint8 *m_KeYStates;

    void keyUp();
    void keyDown();
};


#endif //KeyboardController_H
