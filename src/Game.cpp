#include "Game.h"
#include "TextureManager.h"
#include "Dino.h"

Game* Game::s_Instance = nullptr;

Dino *dino = nullptr;

bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Yay it's running", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window) {
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    TextureManager::getInstance()->loadTexture("dino", "../assets/images/dino_anim.png");

    dino = new Dino(new Properties("dino", 100.0f, 200.0f, 24, 24));
    return m_isRunning = true;
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            quit();
            break;
    }
}

void Game::update() {
    dino->update(0.0f);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 124, 210, 254, 255);
    SDL_RenderClear(renderer);

    dino->draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    TextureManager::getInstance()->clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Game::quit() {
    m_isRunning = false;
}

