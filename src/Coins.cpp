//
// Created by Daniel M Brasil on 8/10/20.
//

#include "Coins.h"
#include "TextureManager.h"

Coins::Coins(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(0, 0, 0, 0);
    collider->setBox((int) properties->X, (int) properties->Y, 32, 32);

    animation = new Animation();
    animation->setProperties("coins", 0, 61, 50);
}

Coins::~Coins() {
    delete collider;
    delete animation;
}

void Coins::draw() {
    animation->draw(transform->x, transform->y, width, height, 1);

   /*  Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= (int) cam.x;
    box.y -= (int) cam.y;
    SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box);*/
}

void Coins::update(float delta) {
    animation->update();
}

SDL_Rect Coins::getCollider() {
    return collider->getBox();
}

void Coins::clean() {
    TextureManager::getInstance()->drop(textureID);
}

