//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Animation_H
#define Animation_H

#include <string>
#include <SDL2/SDL.h>

class Animation {
public:
    Animation() = default;
    void update();
    void draw(float x, float y, int spriteWidth, int spriteHeight);
    void setProperties(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};


#endif //Animation_H
