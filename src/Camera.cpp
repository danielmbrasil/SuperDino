//
// Created by Daniel M Brasil on 6/30/20.
//

#include "Camera.h"

Camera *Camera::s_Instance = nullptr;

void Camera::update() {
    if (target != nullptr) {
        viewBox.x = target->x - SCREEN_WIDTH / 2;
        viewBox.y = target->y - SCREEN_HEIGHT / 2;

        if (viewBox.x < 0)
            viewBox.x = 0;
        if (viewBox.y < 0)
            viewBox.y = 0;

        if (viewBox.x > (2 * SCREEN_WIDTH - viewBox.w))
            viewBox.x = (2 * SCREEN_WIDTH - viewBox.w);

        if (viewBox.y > (SCREEN_HEIGHT - viewBox.h))
            viewBox.y = SCREEN_HEIGHT - viewBox.h;

        position = Vector2D(viewBox.x, viewBox.y);
    }
}
