//
// Created by Daniel M Brasil on 6/28/20.
//

#ifndef MapParser_H
#define MapParser_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser {
public:
    inline static MapParser* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
    }

    bool load();
    void clean();

    inline GameMap* getMaps(std::string id) {return m_Maps[id]; }

private:
    MapParser() = default;
    static MapParser* s_Instance;
    std::map<std::string, GameMap *> m_Maps;

    bool parse(const std::string& id, const std::string& source);
    Tileset parseTileset(TiXmlElement* xmlTileset);
    TileLayer* parseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);
};


#endif //MapParser_H
