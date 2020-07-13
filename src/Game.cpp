#include "Game.h"
#include "TextureManager.h"
#include "Dino.h"
#include "KeyboardController.h"
#include "Clock.h"
#include "MapParser.h"
#include "Camera.h"
#include "UILabel.h"
#include <sstream>
#include "HPBar.h"

Game* Game::s_Instance = nullptr;
UILabel *label;
Dino *dino = nullptr;

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

    if (!MapParser::getInstance()->load()) {
        SDL_Log("Failed to load map.");
        Game::getInstance()->quit();
    }

    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize TTF %s\n", SDL_GetError());
        Game::getInstance()->quit();
    }

    levelMap = MapParser::getInstance()->getMaps("MAP");

    TextureManager::getInstance()->parseTexture("../assets/textures.xml");

    dino = new Dino(new Properties("dino", 100.0f, 300.0f, 24, 24));

    FontManager::getInstance()->addFont("minecraft", "../assets/fonts/Minecraft.ttf", 16);

    SDL_Color yellow = { 248, 160, 0 };
    label = new UILabel(10, 10, "Life Status", "minecraft", yellow);

    Camera::getInstance()->setTarget(dino->getOrigin());

    return m_isRunning = true;
}

void Game::handleEvents() {
    KeyboardController::getInstance()->listen();
}

void Game::update() {

    float delta = Clock::getInstance()->getDeltaTime();

  /*  std::stringstream ss;
    ss << "Dino's life: " << (int) dino->getLife().top() / 10;
    label->setLabelText(ss.str(), "minecraft"); */

    HPBar::update(dino->getLife().top());

    levelMap->update();
    dino->update(delta);
    Camera::getInstance()->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 91, 110, 225, 255);
    SDL_RenderClear(renderer);

    levelMap->render();
    dino->draw();
    HPBar::RenderHPBar(10, 30, 100, 10, HPBar::color(11, 102, 35, 255),
            HPBar::color(202, 52, 51, 255));
    label->draw();
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
