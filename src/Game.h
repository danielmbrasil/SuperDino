#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.h"
#include "StateManager.h"
#include "MenuState.h"
#include "PlayState.h"

class PlayState;

class Game {
public:
    static Game* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
    }

    bool init();

    void update();
    static void handleEvents();
    void render();
    void quit();
    void clean();

    inline bool isRunning() const { return m_isRunning; }
    inline SDL_Renderer* getRenderer() { return renderer; }
    inline PlayState* getPlayState() { return playState; }
private:
    Game() = default;
    static Game* s_Instance;
    bool m_isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    StateManager manager;
    MenuState *menu{};
    PlayState *playState{};
};

#endif //GAME_H