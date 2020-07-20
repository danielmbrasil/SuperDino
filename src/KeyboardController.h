//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef KeyboardController_H
#define KeyboardController_H

#include <SDL2/SDL.h>

class KeyboardController {
public:
    static KeyboardController *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new KeyboardController();
    }

    void listen();

    bool getKeyDown(SDL_Scancode key);

    inline int getX() const { return x; }

    inline int getY() const { return y; }

    inline bool getMouseButtonDown() const { return mouseButtonDown; }

    inline void setMouseButtonDown(bool state) { mouseButtonDown = state; }

private:
    KeyboardController();

    static KeyboardController *s_Instance;
    int x{}, y{};
    bool mouseButtonDown = false;

    SDL_Event event{};
    Uint8 *m_KeYStates;

    void keyDown();

};


#endif //KeyboardController_H
