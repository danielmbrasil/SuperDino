#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"
#include <string>
#include <map>
#include "Camera.h"

class TextureManager {
public:
    static TextureManager *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
    }

    bool loadTexture(const std::string &id, const std::string &filename);

    void drop(const std::string &id);

    void parseTexture(const std::string &src);

    void clean();

    void draw(const std::string &id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale = 1.f);

    void drawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame, int scale = 1,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawTile(const std::string &tilesetID, int tileSize, int x, int y, int row, int frame,
                  SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    TextureManager() = default;

    static TextureManager *s_Instance;

    SDL_Surface *surface{};
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};
    std::map<std::string, SDL_Texture *> texturesMap;

    Vector2D camera;
};

#endif