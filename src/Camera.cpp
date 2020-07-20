//
// Created by Daniel M Brasil on 6/30/20.
//

#include "Camera.h"

Camera *Camera::s_Instance = nullptr;

void Camera::update() {
    if (target != nullptr) {
        viewBox.x = (int) target->x - SCREEN_WIDTH / 2;
        viewBox.y = (int) target->y - SCREEN_HEIGHT / 2;

        if (viewBox.x < 0)
            viewBox.x = 0;
        if (viewBox.y < 0)
            viewBox.y = 0;

        if (viewBox.x > (MAP_WIDTH - viewBox.w))
            viewBox.x = (MAP_WIDTH - viewBox.w);

        if (viewBox.y > (SCREEN_HEIGHT - viewBox.h))
            viewBox.y = SCREEN_HEIGHT - viewBox.h;

        position = Vector2D((float) viewBox.x, (float) viewBox.y);
    }
}
