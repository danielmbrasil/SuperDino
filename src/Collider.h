//
// Created by Daniel M Brasil on 7/2/20.
//

#ifndef Collider_H
#define Collider_H

#include <SDL2/SDL.h>

class Collider {
public:
    inline SDL_Rect getBox() { return m_Box; }
    inline void setBuffer(int x, int y, int w, int h) {
        m_Buffer = { x, y, w, h };
    }

    void setBox(int x, int y, int w, int h) {
        m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h
        };
    }

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};


#endif //Collider_H
