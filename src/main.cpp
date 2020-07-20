#include "Game.h"
#include "Clock.h"

int main(int argc, char *argv[]) {

    Game::getInstance()->init();

    while (Game::getInstance()->isRunning()) {
        Game::getInstance()->handleEvents();
        Game::getInstance()->update();
        Game::getInstance()->render();
        Clock::getInstance()->tick();
    }

    Game::getInstance()->clean();
    return 0;
}