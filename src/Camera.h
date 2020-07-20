//
// Created by Daniel M Brasil on 6/30/20.
//

#ifndef Camera_H
#define Camera_H

#include "Vector2D.h"
#include "Game.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 6400

class Camera {
public:
    static Camera *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
    }

    inline SDL_Rect getViewBox() { return viewBox; }

    inline Vector2D getPosition() { return position; }

    inline void setTarget(Vector2D *tg) { target = tg; }

    void update();

private:
    Camera() {
        viewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    }

    static Camera *s_Instance;

    Vector2D *target{};
    Vector2D position;

    SDL_Rect viewBox{};
};


#endif //Camera_H
