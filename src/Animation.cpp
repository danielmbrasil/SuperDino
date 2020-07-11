//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Animation.h"

#include <utility>
#include "TextureManager.h"

void Animation::update() {
    m_SpriteFrame = ((int)SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::draw(float x, float y, int spriteWidth, int spriteHeight, int sc) {
    TextureManager::getInstance()->drawFrame(m_TextureID, (int)x, (int)y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, sc, m_Flip);
}

void
Animation::setProperties(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_TextureID = std::move(textureID);
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}
