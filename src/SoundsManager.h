//
// Created by Daniel M Brasil on 18/08/2020.
//

#ifndef SoundsManager_H
#define SoundsManager_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class SoundsManager {
public:
    static SoundsManager *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundsManager();
    }

    void loadMusic(const std::string &id, const std::string &source);

    void loadSoundEffect(const std::string &id, const std::string &source);

    void playMusic(const std::string &id);

    void playSoundEffect(const std::string &id);

    void parseSounds(const std::string &source);

    void stopMusic();

    void pauseMusic();

    void clear();


private:
    SoundsManager();

    static SoundsManager *s_Instance;

    std::map<std::string, Mix_Chunk *> soundEffects_map;
    std::map<std::string, Mix_Music *> music_map;
};


#endif //SoundsManager_H
