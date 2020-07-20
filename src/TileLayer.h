//
// Created by Daniel M Brasil on 6/28/20.
//

#ifndef TileLayer_H
#define TileLayer_H

#include "Layer.h"
#include <string>
#include <vector>
#include "TextureManager.h"

struct Tileset {
    int firstID, lastID;
    int rowCount, colCount;
    int tileCount, tileSize;
    std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer {
public:
    TileLayer(int ts, int rowc, int colc, TileMap tilemap, TilesetList tilesets);

    void render() override;

    void update() override;

    inline TileMap getTileMap() { return m_TileMap; }


private:
    int m_tileSize;
    int m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TilesetList m_Tilesets;
};


#endif //TileLayer_H
