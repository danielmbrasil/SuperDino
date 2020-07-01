//
// Created by Daniel M Brasil on 6/28/20.
//

#include "MapParser.h"

#include <utility>

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::load() {
    return parse("MAP", "../assets/maps/map.tmx");
}

void MapParser::clean() {
    std::map<std::string, GameMap *>::iterator iterator;
    for (iterator = m_Maps.begin(); iterator != m_Maps.end(); iterator++)
        iterator->second = nullptr;
    m_Maps.clear();
}

bool MapParser::parse(const std::string& id, const std::string& source) {
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();

    int width, height;
    int tilesize = 0;

    root->Attribute("width", &width);
    root->Attribute("height", &height);
    root->Attribute("tilewidth", &tilesize);

    // parse tilesets
    TilesetList tilesets;
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(parseTileset((e)));
        }
    }

    // parse layers
    auto* gameMap = new GameMap();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer *tileLayer = parseTileLayer(e, tilesets, tilesize, height, width);
            gameMap->m_MapLayers.push_back(tileLayer);
        }
    }

    m_Maps[id] = gameMap;

    return true;
}

Tileset MapParser::parseTileset(TiXmlElement *xmlTileset) {
    Tileset tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.firstID);
    xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.colCount);
    tileset.rowCount = tileset.tileCount / tileset.colCount;
    xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement *image = xmlTileset->FirstChildElement();
    tileset.source = image->Attribute("source");

    return tileset;
}

TileLayer *
MapParser::parseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount) {
    TiXmlElement *data;

    for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            getline(iss, id, ',');
            std::stringstream converter(id);
            converter >> tileMap[row][col];

            if (!iss.good())
                break;
        }
    }

    return (new TileLayer(tileSize, rowCount, colCount, tileMap, std::move(tilesets)));
}
