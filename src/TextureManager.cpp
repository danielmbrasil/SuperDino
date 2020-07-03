#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::loadTexture(const std::string& id, const std::string& filename) {
    surface = IMG_Load(filename.c_str());

    if (!surface) {
        SDL_Log("Failed to load surface: %s\n", SDL_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);

    if (!texture) {
        SDL_Log("Failed to load texture: %s\n", SDL_GetError());
        return false;
    }

    texturesMap[id] = texture;

    return true;
}

void TextureManager::draw(const std::string& id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    srcRect = { 0, 0, width, height };
    camera = Camera::getInstance()->getPosition();
    destRect = { static_cast<int>((float)x - camera.x), static_cast<int>((float)y - camera.y), width, height };

    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                               SDL_RendererFlip flip) {
    srcRect = {width * frame, height * row, width, height };
    camera = Camera::getInstance()->getPosition();
    destRect = {static_cast<int>((float)x - camera.x), static_cast<int>((float)y - camera.y), width, height };
    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawTile(const std::string &tilesetID, int tileSize, int x, int y, int row, int frame,
                              SDL_RendererFlip flip) {
    camera = Camera::getInstance()->getPosition();
    destRect = { static_cast<int>((float)x - camera.x), static_cast<int>((float)y - camera.y), tileSize, tileSize };
    srcRect = { tileSize*frame, tileSize*row, tileSize, tileSize };
    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texturesMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drop(const std::string& id) {
    SDL_DestroyTexture(texturesMap[id]);
    texturesMap.erase(id);
}

void TextureManager::clean() {
    std::map<std::string, SDL_Texture *>::iterator iterator;

    for (iterator = texturesMap.begin(); iterator != texturesMap.end(); iterator++)
        SDL_DestroyTexture(iterator->second);

    texturesMap.clear();

    SDL_Log("Texture map cleaned.");
}
