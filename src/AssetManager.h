#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager {
public:
    explicit AssetManager(Manager *man);

    ~AssetManager();

    //texture management
    void AddTexture(const std::string &id, const char *path);

    SDL_Texture *GetTexture(const std::string &id);


private:
    Manager *manager;
    std::map<std::string, SDL_Texture *> textures;
};

#endif