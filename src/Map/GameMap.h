#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <iostream>
#include <vector>
#include "Chunk.h"

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

    inline Tile getTile(int x, int y, int z = FOREGROUND)const{
        return chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->getTile( x%8, y%8, z);
    }

    inline void setTile(int x, int y, int z, Tile tile){
        chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->setTile( x%CHUNK_WIDTH, y%CHUNK_HEIGHT, z, tile );
    }

    inline void dropTile(int x, int y, int z){
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

    void displayToMapPosition(int *x, int *y);
    
    Tileset *tileset;

private:
    friend class MapParser;
    ChunkList chunks;
    const MapSize chunkWidth, chunkHeight;
    const int     pixelWidth, pixelHeight;
    const int     tileWidth,  tileHeight;

};

#endif // GAMEMAP_H
