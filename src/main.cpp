#include "Game.h"

int main(int argc, char *argv[]) {

    Game::getInstance()->init();

    while(Game::getInstance()->isRunning()) {
        Game::getInstance()->handleEvents();
        Game::getInstance()->update();
        Game::getInstance()->render();
    }

    Game::getInstance()->clean();
    return 0;
}