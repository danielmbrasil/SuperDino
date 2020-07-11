//
// Created by Daniel M Brasil on 7/9/20.
//

#include "FontManager.h"

FontManager* FontManager::s_Instance = nullptr;

void FontManager::addFont(const std::string& id, const std::string& path, int fontSize) {
    fontsMap.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font *FontManager::getFont(const std::string& id) {
    return fontsMap[id];
}
