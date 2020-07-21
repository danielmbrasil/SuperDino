//
// Created by daniel on 17/07/2020.
//

#include "PlayState.h"
#include "MapParser.h"
#include "ObjectManager.h"
#include <sstream>

PlayState::PlayState(float x, float y) {
    // get renderer context
    m_Context = Game::getInstance()->getRenderer();

    // load level 1 map
    levelMap_1 = MapParser::getInstance()->getMaps("MAP");
    TextureManager::getInstance()->parseTexture("../assets/textures.xml");

    // create Dino
    auto *dinoProperties = new Properties("dino", x, y, 24, 24);
    dino = ObjectManager::getInstance()->createObject("DINO", dinoProperties);

    dino->initLife();

    // load fonts and create lifeLabel
    FontManager::getInstance()->addFont("minecraft", "../assets/fonts/Minecraft.ttf", 16);
    SDL_Color yellow = {248, 160, 0};
    lifeLabel = new UILabel(10, 10, "Dino", "minecraft", yellow);

    // create camera
    Camera::getInstance()->setTarget(dino->getOrigin());
}

void PlayState::render() {
    //SDL_SetRenderDrawColor(m_Context, 91, 110, 225, 255);
    SDL_RenderClear(m_Context);

    levelMap_1->render();
    dino->draw();
    lifeLabel->draw();

    SDL_Rect camera = Camera::getInstance()->getViewBox();

    SDL_RenderCopy(m_Context, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Context);
}

void PlayState::update(float dt) {
    std::stringstream ss;
    ss << "Dino x" << dino->getLife().top();
    lifeLabel->clean();
    lifeLabel->setLabelText(ss.str(), "minecraft");

    levelMap_1->update();
    dino->update(dt);

    Camera::getInstance()->update();
}

void PlayState::clear() {
    dino->clean();
    lifeLabel->clean();
    delete lifeLabel;
}
