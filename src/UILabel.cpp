//
// Created by Daniel M Brasil on 7/10/20.
//

#include "UILabel.h"

UILabel::UILabel(int x, int y, std::string text, std::string font, SDL_Color &color) :
        labelText(std::move(text)), labelFont(std::move(font)), textColor(color)
{
    position.x = x;
    position.y = y;

    setLabelText(labelText, labelFont);
}

void UILabel::setLabelText(const std::string &text, const std::string &font) {
    SDL_Surface *surface = TTF_RenderText_Blended(FontManager::getInstance()->getFont(font), text.c_str(), textColor);
    if(!surface) {
        SDL_Log("Failed to load surface %s\n", SDL_GetError());
        return;
    }

    labelTexture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);
    if(!labelTexture) {
        SDL_Log("Failed to create texture %s\n", SDL_GetError());
        return;
    }

    SDL_FreeSurface(surface);

    SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
}

void UILabel::draw() {
    SDL_RenderCopy(Game::getInstance()->getRenderer(), labelTexture, nullptr, &position);
}