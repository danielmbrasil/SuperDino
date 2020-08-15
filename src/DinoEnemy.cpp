//
// Created by daniel on 7/26/20.
//

#include "DinoEnemy.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Camera.h"
#include <iostream>

DinoEnemy::DinoEnemy(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(0, -8, -10, -6);
    collider->setBox((int) properties->X, (int) properties->Y, 24, 24);

    head = new Collider();
    head->setBuffer(-10, 0, 0, 10);
    head->setBox((int) properties->X, (int) properties->Y, 24, 24);

    rigidBody = new RigidBody();

    animation = new Animation();
    animation->setProperties(textureID, 0, 8, 100);

    isForward = false;
    initialPosition = properties->X;
}

DinoEnemy::~DinoEnemy() {
    delete collider;
    delete rigidBody;
    delete animation;
}

void DinoEnemy::draw() {
    animation->draw(transform->x, transform->y, width, height, 2);

   /* Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= (int) cam.x;
    box.y -= (int) cam.y;
    SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box);*/
}

void DinoEnemy::update(float delta) {
    rigidBody->update(delta);

    lastPosition.x = transform->x;
    transform->moveX(rigidBody->getPosition().x);
    collider->setBox((int) transform->x, (int) transform->y, 24, 24);
    head->setBox((int) transform->x, (int) transform->y, 24, 24);

    if (Camera::getInstance()->getPosition().x > (initialPosition - 850.f)) {
        if (!isForward) {
            animation->setProperties("dino_enemy", 0, 8, 100, SDL_FLIP_HORIZONTAL);
            rigidBody->applyForceX(-3.f);
        }
        if (Collision::getInstance()->mapCollision(collider->getBox())) {
            transform->x = lastPosition.x;
            isForward = !isForward;
            if (!isForward) {
                animation->setProperties("dino_enemy", 0, 8, 100, SDL_FLIP_HORIZONTAL);
                rigidBody->applyForceX(-3.f);
            } else {
                animation->setProperties("dino_enemy", 0, 8, 100);
                rigidBody->applyForceX(3.f);
            }
        } 
    }

    if (transform->y < 430.f) {
        lastPosition.y = transform->y;
        transform->moveY(rigidBody->getPosition().y);
        collider->setBox((int) transform->x, (int) transform->y, 24, 24);
        head->setBox((int) transform->x, (int) transform->y, 24, 24);

        if (Collision::getInstance()->mapCollision(collider->getBox()))
            transform->y = lastPosition.y;
    } else {
        suicide();
    }
    origin->x = transform->x + (float) width / 2;
    origin->y = transform->y + (float) height / 2;

    animation->update();
}

SDL_Rect DinoEnemy::getCollider() {
    return collider->getBox();
}

SDL_Rect DinoEnemy::getHeadCollider() {
    return head->getBox();
}

void DinoEnemy::clean() {
    TextureManager::getInstance()->drop(textureID);
}

void DinoEnemy::suicide() {
    Game::getInstance()->getPlayState()->enemySuicide(this);
    //delete this;
}
