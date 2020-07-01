//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Dino.h"
#include "TextureManager.h"
#include "KeyboardController.h"

Dino::Dino(Properties *properties) : Character(properties) {
    animation = new Animation();
    rigidBody = new RigidBody();
    animation->setProperties(textureID, 0, 3, 100);
}

void Dino::draw() {
    animation->draw(transform->x, transform->y, width, height);
}

void Dino::clean() {
    TextureManager::getInstance()->clean();
}

void Dino::update(float delta) {
    animation->setProperties("dino", 0, 3, 100);
    rigidBody->zeroForce();

    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_D))) {
        rigidBody->applyForceX(5.0f);
        animation->setProperties("dino_running", 0, 6, 100);
    }
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_A))) {
        rigidBody->applyForceX(-5.0f);
        animation->setProperties("dino_running", 0, 6, 10, SDL_FLIP_HORIZONTAL);
    }

    rigidBody->update(delta);
    transform->moveX(rigidBody->getPosition().x);

    origin->x = transform->x + width/2;
    origin->y = transform->y + height/2;

    animation->update();
}
