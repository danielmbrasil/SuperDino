//
// Created by Daniel M Brasil on 7/9/20.
//

#ifndef FontManager_H
#define FontManager_H

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontManager {
public:
    static FontManager* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new FontManager();
    }
    void addFont(const std::string& id, const std::string& path, int fontSize);
    TTF_Font* getFont(const std::string& id);

private:
    FontManager() = default;
    static FontManager *s_Instance;
    std::map<std::string, TTF_Font *> fontsMap;
};


#endif //FontManager_H
