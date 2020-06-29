//
// Created by Daniel M Brasil on 6/28/20.
//

#include "TileLayer.h"

TileLayer::TileLayer(int ts, int rowc, int colc, TileMap &tilemap, TilesetList &tilesets) {
    m_tileSize = ts;
    m_RowCount = rowc;
    m_ColCount = colc;
    m_TileMap = tilemap;
    m_Tilesets = tilesets;

    for (auto & m_Tileset : m_Tilesets) {
        TextureManager::getInstance()->loadTexture("dino", "../assets/maps/" + m_Tileset.source);
    }
}

void TileLayer::render() {
    for (unsigned int i = 0; i < m_RowCount; i++) {
        for (unsigned int j = 0; j < m_ColCount; j++) {
            int tileID = m_TileMap[j][j];

            if (tileID == 0) continue;

            else {
                int ts_index;
                if (m_Tilesets.size() > 1) {
                    for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
                        if (tileID > m_Tilesets[k].firstID && tileID < m_Tilesets[k].lastID) {
                            tileID = tileID + m_Tilesets[k].tileCount - m_Tilesets[k].lastID;
                            ts_index = (int)k;
                            break;
                        }
                    }
                }


                Tileset ts = m_Tilesets[ts_index];
                int tileRow = tileID / ts.colCount;
                int tileCol = tileID - tileRow * ts.colCount - 1;

                // if the tile is in the last column
                if (tileID % ts.colCount == 0) {
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }

                // draw
                //TextureManager::drawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
                //TextureManager::Draw()
            }
        }
    }
}

void TileLayer::update() {

}
