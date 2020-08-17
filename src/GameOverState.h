//
// Created by Daniel M Brasil on 8/15/20.
//

#ifndef GameOverState_H
#define GameOverState_H

#include "GameState.h"
#include "UILabel.h"
#include <string>
#include <vector>

class GameOverState : public GameState {
public:
    GameOverState(int life, int coins, int score);

    ~GameOverState() override;

    void update(float dt) override;

    void render() override;

    void events();

private:
    UILabel *labels[3]{};
    std::vector<UILabel *> v_labels;

    std::string options[3] = {"New Game", "Return to Main Menu", "Exit"};

    SDL_Rect position[3]{};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color yellow = {248, 160, 0};

    int finalLife;
    int collectedCoins;
    int score;
};


#endif //GameOverState_H
