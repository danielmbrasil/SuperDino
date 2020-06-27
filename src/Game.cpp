#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 900, 900};

AssetManager *Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto &player(manager.addEntity());

Game::Game() = default;

Game::~Game() = default;

void Game::init(const char *title, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (!window)
            SDL_Log("Failed to create window %s\n", SDL_GetError());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer)
            SDL_SetRenderDrawColor(renderer, 135, 206, 235, 1);
        else
            SDL_Log("Failed to crete renderer %s\n", SDL_GetError());

        isRunning = true;
    } else
        SDL_Log("Failed to initialize %s\n", SDL_GetError());

    assets->AddTexture("player", "../assets/images/dino.png");


    //ECS implementation
    player.addComponent<TransformComponent>(100.0f, 500.0f, 32, 32, 1);
    player.addComponent<SpriteComponent>("player");
    player.addComponent<KeyboardController>();
    player.addGroup(groupPlayer);
}

auto &players(manager.getGroup(Game::groupPlayer));

void Game::handleEvents() {

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT :
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    manager.refresh();
    manager.update();

    camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
    camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
}

void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &p : players)
        p->draw();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
