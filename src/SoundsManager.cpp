//
// Created by Daniel M Brasil on 18/08/2020.
//

#include "SoundsManager.h"
#include <iostream>
#include "../vendor/tinyxml/tinyxml.h"

SoundsManager *SoundsManager::s_Instance = nullptr;

SoundsManager::SoundsManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        std::cerr << Mix_GetError() << std::endl;
}

void SoundsManager::loadMusic(const std::string &id, const std::string &source) {
    Mix_Music *music = Mix_LoadMUS(source.c_str());

    if (music)
        music_map[id] = music;
    else
        std::cerr << Mix_GetError() << "in : " << id << std::endl;
}

void SoundsManager::loadSoundEffect(const std::string &id, const std::string &source) {
    Mix_Chunk *chunk = Mix_LoadWAV(source.c_str());

    if (chunk)
        soundEffects_map[id] = chunk;
    else
        std::cerr << Mix_GetError() << "in : " << id << std::endl;
}

void SoundsManager::playMusic(const std::string &id) {
    if (Mix_PlayMusic(music_map[id], -1) == -1)
        std::cerr << Mix_GetError() << "error playing : " << id << std::endl;
}

void SoundsManager::playSoundEffect(const std::string &id) {
    if (Mix_PlayChannel(1, soundEffects_map[id], 0) == -1)
        std::cerr << Mix_GetError() << "error playing : " << std::endl;
}

void SoundsManager::parseSounds(const std::string &source) {
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error())
        std::cerr << "Failed to load file: " << source << std::endl;

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("effect")) {
            loadSoundEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
        else if (e->Value() == std::string("music")) {
            loadMusic(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }
}

void SoundsManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundsManager::pauseMusic() {
    Mix_PauseMusic();
}

void SoundsManager::clear() {
    for (auto & it : music_map)
        Mix_FreeMusic(it.second);
    for (auto & it : soundEffects_map)
        Mix_FreeChunk(it.second);

    music_map.clear();
    soundEffects_map.clear();
}
