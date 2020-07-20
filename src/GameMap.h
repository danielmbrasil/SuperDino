//
// Created by Daniel M Brasil on 6/28/20.
//

#ifndef GameMap_H
#define GameMap_H

#include "Layer.h"
#include <vector>


class GameMap {
public:
    void render() {
        for (auto &m_MapLayer : m_MapLayers)
            m_MapLayer->render();
    }

    void update() {
        for (auto &m_MapLayer : m_MapLayers)
            m_MapLayer->update();
    }

    void clean() {
        m_MapLayers.clear();
    }

    std::vector<Layer *> getMapLayers() { return m_MapLayers; }

private:
    friend class MapParser;

    std::vector<Layer *> m_MapLayers;
};


#endif //GameMap_H
