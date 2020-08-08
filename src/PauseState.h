//
// Created by daniel on 7/19/20.
//

#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include <string>
#include "UILabel.h"

class PauseState : public GameState {
public:
    PauseState();

    ~PauseState();

    void update(float dt) override;

    void render() override;

    void events();

private:
    UILabel *labels[3]{};
    std::string options[3] = {"Resume Game", "Return to Main Menu", "Exit"};

    SDL_Rect position[3]{};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color green = {0, 255, 0, 255};
};


#endif //PAUSESTATE_H
