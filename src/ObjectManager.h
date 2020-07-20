//
// Created by daniel on 16/07/2020.
//

#ifndef INC_2D_SUPERDINO_OBJECTMANAGER_H
#define INC_2D_SUPERDINO_OBJECTMANAGER_H

#include <map>
#include <string>
#include <functional>
#include "GameObject.h"

class ObjectManager {
public:
    static ObjectManager *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectManager();
    }

    GameObject *createObject(const std::string &type, Properties *properties);

    void registerType(const std::string &className, std::function<GameObject *(Properties *properties)> type);

private:
    ObjectManager() = default;

    static ObjectManager *s_Instance;
    std::map<std::string, std::function<GameObject *(Properties *properties)>> m_TypeRegistry;
};

template<typename T>
class Register {
public:
    explicit Register(const std::string &className) {
        ObjectManager::getInstance()->registerType(className, [](Properties *properties) -> GameObject * {
            return new T(properties);
        });
    }
};

#endif //INC_2D_SUPERDINO_OBJECTMANAGER_H
