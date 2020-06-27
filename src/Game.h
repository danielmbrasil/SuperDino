#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;

class ColliderComponent;

class Game {
private:
    SDL_Window *window{};

public:
    Game();

    ~Game();

    void init(const char *title, int width, int height, bool fullscreen);

    static void handleEvents();

    static void update();

    static bool running() { return isRunning; }

    static void render();

    void clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager *assets;
    enum groupLabels : std::size_t {
        groupMap,
        groupPlayer,
        groupColliders
    };
};

#endif //GAME_H