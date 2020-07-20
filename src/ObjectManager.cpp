//
// Created by daniel on 16/07/2020.
//

#include "ObjectManager.h"

#include <utility>

ObjectManager *ObjectManager::s_Instance = nullptr;

GameObject *ObjectManager::createObject(const std::string &type, Properties *properties) {
    GameObject *object = nullptr;
    auto it = m_TypeRegistry.find(type);

    if (it != m_TypeRegistry.end())
        object = it->second(properties);

    return object;
}

void ObjectManager::registerType(const std::string &className, std::function<GameObject *(Properties *)> type) {
    m_TypeRegistry[className] = std::move(type);
}
