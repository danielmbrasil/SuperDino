//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Dino.h"
#include "TextureManager.h"
#include "KeyboardController.h"
#include "Collision.h"

Dino::Dino(Properties *properties) : Character(properties) {
    initLife();

    jumpTime = JUMP_TIME;
    jumpForce = JUMP_FORCE;

    collider = new Collider();
    collider->setBuffer(0, 0, -12 ,-16);

    rigidBody = new RigidBody();
    rigidBody->setGravity(4.0f);

    animation = new Animation();
    animation->setProperties(textureID, 0, 3, 100);
}

void Dino::draw() {
    animation->draw(transform->x, transform->y, width, height, 2);

   /* Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= (int)cam.x;
    box.y -= (int)cam.y;

    SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box); */
}

void Dino::update(float delta) {
    animation->setProperties("dino", 0, 3, 100);
    rigidBody->zeroForce();

    // run forward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_D))) {
        rigidBody->applyForceX(5.0f);
        animation->setProperties("dino_running", 0, 6, 100);
    }

    // run backward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_A))) {
        rigidBody->applyForceX(-5.0f);
        animation->setProperties("dino_running", 0, 6, 10, SDL_FLIP_HORIZONTAL);
    }

    // jump
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_W)) && isOnGround) {
        isJumping = true;
        isOnGround = false;
        rigidBody->applyForceY(jumpForce * (-1));
    }
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_W)) && isJumping && jumpTime > 0) {
        jumpTime -= delta;
        rigidBody->applyForceY(jumpForce * (-1));
    } else {
        isJumping = false;
        jumpTime = JUMP_TIME;
    }

    rigidBody->update(delta);

    // move on X axis
    lastPosition.x = transform->x;
    transform->moveX(rigidBody->getPosition().x);
    collider->setBox((int) transform->x, (int) transform->y, 24, 24);

    if (Collision::getInstance()->mapCollision(collider->getBox()))
        transform->x = lastPosition.x;

    if (Collision::getInstance()->cactusCollision(collider->getBox())) {
        animation->setProperties("dino_crying", 0, 2, 500);
        loseLife();
        transform->x = lastPosition.x;
    }

    if(transform->x < 0 || transform->x > MAP_WIDTH)
        transform->x = lastPosition.x;

    // move on Y axis
    lastPosition.y = transform->y;
    transform->moveY(rigidBody->getPosition().y);
    collider->setBox((int)transform->x, (int)transform->y, 24, 24);

    if (Collision::getInstance()->mapCollision(collider->getBox())) {
        isOnGround = true;
        transform->y = lastPosition.y;
    }
    else isOnGround = false;


    origin->x = transform->x + (float)width/2;
    origin->y = transform->y + (float)height/2;

    animation->update();
}

void Dino::clean() {
    TextureManager::getInstance()->drop(textureID);
}
