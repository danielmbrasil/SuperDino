//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Dino.h"
#include "TextureManager.h"

Dino::Dino(Properties *properties) : Character(properties) {
    m_Row = 0;
    m_FrameCount = 3;
    animSpeed = 100;
}

void Dino::draw() {
    TextureManager::getInstance()->drawFrame(textureID, (int)transform->x, (int)transform->y, width, height, m_Row, m_Frame);
}

void Dino::clean() {
    TextureManager::getInstance()->clean();
}

void Dino::update(float delta) {
    m_Frame = ((int)SDL_GetTicks() / animSpeed) % m_FrameCount;
}
