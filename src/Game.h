#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.h"
#include "StateManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "VoidState.h"

class PlayState;

class MenuState;

class PauseState;

class VoidState;

class Game {
public:
    static Game *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
    }

    bool init();

    void update();

    void handleEvents();

    void render();

    void quit();

    void clean();

    inline bool isRunning() const { return m_isRunning; }

    inline SDL_Renderer *getRenderer() { return renderer; }

    inline PlayState *getPlayState() { return playState; }

    inline StateManager *getManager() { return &manager; }

    inline PauseState *getPauseState() { return pauseState; }

    inline VoidState *getVoidState() { return voidState; }

    inline void unsetPlayState() {
        delete playState;
        playState = nullptr;
    }

    inline void unsetMenu() {
        delete menu;
        menu = nullptr;
    }

    inline void unsetPause() {
        delete pauseState;
        pauseState = nullptr;
    }

    inline void unsetVoidState() {
        delete voidState;
        voidState = nullptr;
    }

    void startGame();

    void newMenu();

    void newVoidState();

private:
    Game() = default;

    static Game *s_Instance;
    bool m_isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    StateManager manager;
    MenuState *menu{};
    PlayState *playState{};
    PauseState *pauseState{};
    VoidState *voidState{};

};

#endif //GAME_H