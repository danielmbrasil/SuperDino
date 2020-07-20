#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.h"
#include "StateManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

class PlayState;

class MenuState;

class PauseState;

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

    inline void unsetMenu() { menu = nullptr; }

    inline void unsetPause() { pauseState = nullptr; }

    void startGame();

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
};

#endif //GAME_H