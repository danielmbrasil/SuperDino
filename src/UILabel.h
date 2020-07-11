//
// Created by Daniel M Brasil on 7/9/20.
//

#ifndef UILabel_H
#define UILabel_H


#include "FontManager.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <utility>
#include <iostream>

class UILabel {
public:
    UILabel(int x, int y, std::string  text, std::string  font, SDL_Color& color);

    void setLabelText(const std::string& text, const std::string& font);

    void draw();

private:
    SDL_Rect position{};
    std::string labelText;
    std::string labelFont;
    SDL_Color textColor;
    SDL_Texture *labelTexture{};
};

#endif //UILabel_H
