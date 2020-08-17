//
// Created by Daniel M Brasil on 16/08/2020.
//

#include "Cactus.h"
#include "TextureManager.h"

Cactus::Cactus(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(-22, -25, 45, 25);
    collider->setBox((int) properties->X, (int) properties->Y, (int)(48.f * 1.5), (int)(48.f * 1.5));
}

Cactus::~Cactus() {
    delete collider;
}

void Cactus::draw() {
    TextureManager::getInstance()->draw("cactus", (int) transform->x, (int) transform->y, 48, 48, SDL_FLIP_NONE, 1.5f);

  /*  Vector2D cam = Camera::getInstance()->getPosition();
   SDL_Rect box = collider->getBox();
   box.x -= (int) cam.x;
   box.y -= (int) cam.y;
   SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box); */
}

void Cactus::clean() {
    TextureManager::getInstance()->drop(textureID);
}

void Cactus::update(float delta) {

}

SDL_Rect Cactus::getCollider() {
    return collider->getBox();
}
