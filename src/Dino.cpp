//
// Created by Daniel M Brasil on 6/29/20.
//

#include "Dino.h"
#include "TextureManager.h"
#include "KeyboardController.h"
#include "Collision.h"
#include <vector>

Dino::Dino(Properties *properties) : Character(properties) {

    jumpTime = JUMP_TIME;
    jumpForce = JUMP_FORCE;

    collider = new Collider();
    collider->setBuffer(0, 0, -12, -16);
    collider->setBox((int) properties->X, (int) properties->Y, 24, 24);

    rigidBody = new RigidBody();

    animation = new Animation();
    animation->setProperties(textureID, 0, 3, 100);

    dinoHitFirst = false;

    collectedCoins = 0;
}

Dino::~Dino() {
    delete collider;
    delete rigidBody;
    delete animation;
}

void Dino::draw() {
    animation->draw(transform->x, transform->y, width, height, 2);

   /* Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = feet->getBox();
    box.x -= (int) cam.x;
    box.y -= (int) cam.y;
    SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box); */
}

void Dino::update(float delta) {
    animation->setProperties("dino", 0, 3, 100);
    rigidBody->zeroForce();
    dinoHitFirst = false;

    // walk forward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_D))) {
        rigidBody->applyForceX(3.f);
        animation->setProperties("dino_walking", 0, 6, 100);
    }

    // walk backward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_A))) {
        rigidBody->applyForceX(-3.f);
        animation->setProperties("dino_walking", 0, 6, 100, SDL_FLIP_HORIZONTAL);
    }

    // run forward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_D)) &&
        KeyboardController::getInstance()->getKeyDown(SDL_SCANCODE_LSHIFT)) {
        rigidBody->applyForceX(5.f);
        animation->setProperties("dino_running", 0, 6, 100);
    }

    // run backward
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_A)) &&
        KeyboardController::getInstance()->getKeyDown(SDL_SCANCODE_LSHIFT)) {
        rigidBody->applyForceX(-5.f);
        animation->setProperties("dino_running", 0, 6, 100, SDL_FLIP_HORIZONTAL);
    }

    // jump
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_SPACE)) && isOnGround) {
        isJumping = true;
        isOnGround = false;
        rigidBody->applyForceY(jumpForce * (-1));
    }
    if (KeyboardController::getInstance()->getKeyDown((SDL_SCANCODE_SPACE)) && isJumping && jumpTime > 0) {
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


    if (transform->x < 0 || transform->x > MAP_WIDTH)
        transform->x = lastPosition.x;

    // move on Y axis
    if (transform->y > 430.f) {
        loseLife();
        transform->x = 100.f;
        transform->y = 300.f;
        clean();
        Game::getInstance()->newVoidState(life);
    }

    lastPosition.y = transform->y;
    transform->moveY(rigidBody->getPosition().y);
    collider->setBox((int) transform->x, (int) transform->y, 24, 24);

    if (Collision::getInstance()->mapCollision(collider->getBox())) {
        isOnGround = true;
        transform->y = lastPosition.y;
    } else isOnGround = false;

    std::vector<DinoEnemy *> enemies = Game::getInstance()->getPlayState()->getEnemies();

    for (int i = 0; i < enemies.size(); i++) {
        SDL_Rect enemyRect, dinoRect;
        enemyRect = enemies[i]->getHeadCollider();
        dinoRect = collider->getBox();

        if (Collision::getInstance()->checkCollision(dinoRect, enemyRect)) {
            dinoHitFirst = true;
            Game::getInstance()->getPlayState()->enemyDeath(i);
        }
    }

    std::vector<Coins *> coins = Game::getInstance()->getPlayState()->getCoins();

    for (int i = 0; i < coins.size(); i++) {
        SDL_Rect coinRect, dinoRect;
        coinRect = coins[i]->getCollider();
        dinoRect = collider->getBox();

        if (Collision::getInstance()->checkCollision(coinRect, dinoRect)) {
            collectedCoins++;
            Game::getInstance()->getPlayState()->eraseCoin(i);
        }
    }

    origin->x = transform->x + (float) width / 2;
    origin->y = transform->y + (float) height / 2;

    animation->update();
}

SDL_Rect Dino::getCollider() {
    return collider->getBox();
}

void Dino::clean() {
    TextureManager::getInstance()->drop(textureID);
}
