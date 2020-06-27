#pragma once

#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <string>
#include <utility>
#include "SDL2/SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public:
    SDL_Rect collider{};
    std::string tag;

    SDL_Texture *tex{};
    SDL_Rect srcR{}, destR{};

    TransformComponent *transform{};

    explicit ColliderComponent(std::string t) {
        tag = std::move(t);
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size) {
        tag = std::move(t);
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }


    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        //tex = TextureManager::LoadTexture("../assets/coltex.png");
        tex = nullptr;
        srcR = {0, 0, 32, 32};
        destR = {collider.x, collider.y, collider.w, collider.h};

    }

    void update() override {
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

private:

};

#endif //COLLIDERCOMPONENT_H