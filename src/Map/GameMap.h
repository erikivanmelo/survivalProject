#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Chunk.h"
#include "../Physics/Vector2D.h"

typedef std::vector<std::vector<Chunk*>> ChunkList;

class GameMap
{
public:

    GameMap( const MapSize width, const MapSize height );

    ~GameMap();
    void render();


    inline void update(){}

    inline Chunk* getChunk(MapSize x, MapSize y)const{
        return chunks[x][y];
    }

    inline Tile *getTile(int x, int y, bool z = FOREGROUND)const{
        return chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->getTile( x%8, y%8, z);
    }

    inline void setTile(int x, int y, bool z, Tile tile){
        if( !tile ){
            chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->setTile( x%CHUNK_WIDTH, y%CHUNK_HEIGHT, z, nullptr);
            return;
        }
        std::unordered_map<Tile, Tile*>::iterator it = tileList.find(tile);
        Tile *tilePtr = (it != tileList.end())? tileList[tile] : tileList[tile] = new Tile(tile);
        chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->setTile( x%CHUNK_WIDTH, y%CHUNK_HEIGHT, z, tilePtr );
    }

    inline void dropTile(int x, int y, bool z){
        chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->dropTile( x%CHUNK_WIDTH, y%CHUNK_HEIGHT, z);
    }


    //TODO re ver los nombres para retornar el tamaño del mapa en distintas unidades
    inline MapSize getChunkHeight() const{
        return chunkHeight;
    }

    inline MapSize getChunkWidth()const{
        return chunkWidth;
    }

    inline int getPixelHeight() const{
        return pixelHeight;
    }

    inline int getPixelWidth()const{
        return pixelWidth;
    }

    inline int getTileHeight() const{
        return tileHeight;
    }

    inline int getTileWidth()const{
        return tileWidth;
    }

    bool areBlockAround(int x, int y, bool z = FOREGROUND, bool inCenterToo = false);

    void displayPositionToMapPosition(Vector2D *position);
    void mapPositionToDisplayPosition(Vector2D *position);

    inline Vector2D snapToGrid(Vector2D position){
        position.x = (int)((int)position.x * tileset->tileSize) / tileset->tileSize;
        position.y = (int)((int)position.y * tileset->tileSize) / tileset->tileSize;
        return position;
    }

    void focusBlock(Vector2D position);
    

private:
    Tileset *tileset;
    friend class MapParser;
    ChunkList chunks;
    unordered_map< Tile , Tile*> tileList;
    const MapSize chunkWidth, chunkHeight;
    const int     pixelWidth, pixelHeight;
    const int     tileWidth,  tileHeight;

};

#endif // GAMEMAP_H
