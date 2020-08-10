#include "Game.h"
#include "TextureManager.h"
#include "KeyboardController.h"
#include "Clock.h"
#include "MapParser.h"

Game *Game::s_Instance = nullptr;

void Game::startGame() {
    playState = new PlayState(100.0f, 300.0f, 3, 0);
    manager.addState(playState);
}

void Game::restartGame(int life, int coins) {
    playState = new PlayState(100.f, 300.f, life, coins);
    manager.addState(playState);
}

void Game::newMenu() {
    menu = new MenuState();
    manager.addState(menu);
}

void Game::newVoidState(int life) {
    voidState = new VoidState(life, Game::getInstance()->getPlayState()->getCollectedCoins());
    manager.addState(voidState);
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Yay it's running", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window) {
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize TTF %s\n", SDL_GetError());
        Game::getInstance()->quit();
    }

    if (!MapParser::getInstance()->load()) {
        SDL_Log("Failed to load map.");
        Game::getInstance()->quit();
    }

    // add fonts
    FontManager::getInstance()->addFont("minecraft", "../assets/fonts/Minecraft.ttf", 16);
    FontManager::getInstance()->addFont("minecraftBigger", "../assets/fonts/Minecraft.ttf", 32);

    playState = nullptr;
    pauseState = nullptr;
    voidState = nullptr;

    // create main menu
    newMenu();

    return m_isRunning = true;
}

void Game::handleEvents() {
    KeyboardController::getInstance()->listen();

    if (KeyboardController::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::getInstance()->pauseState = new PauseState();
        Game::getInstance()->manager.addState(Game::getInstance()->pauseState);
        SDL_Delay(300);
    }
}

void Game::update() {

    float deltaTime = Clock::getInstance()->getDeltaTime();

    if (Game::getInstance()->menu)
        Game::getInstance()->menu->events();

    if (Game::getInstance()->pauseState)
        Game::getInstance()->pauseState->events();

    if (!manager.isEmpty())
        Game::getInstance()->manager.update(deltaTime);
}

void Game::render() {
    if (!manager.isEmpty())
        Game::getInstance()->manager.render();
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
