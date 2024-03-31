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
        return chunks[ x / CHUNK_SQUARE_SIZE ][ y / CHUNK_SQUARE_SIZE ]->getTile(x % CHUNK_SQUARE_SIZE, y % CHUNK_SQUARE_SIZE, z);
    }

    inline void setTile(int x, int y, bool z, Tile tile){
        if( !tile ){
            chunks[ x / CHUNK_SQUARE_SIZE ][ y / CHUNK_SQUARE_SIZE ]->setTile( x % CHUNK_SQUARE_SIZE, y % CHUNK_SQUARE_SIZE, z, nullptr);
            return;
        }
        std::unordered_map<Tile, Tile*>::iterator it = tileList.find(tile);
        Tile *tilePtr = (it != tileList.end())? tileList[tile] : tileList[tile] = new Tile(tile);
        chunks[ x / CHUNK_SQUARE_SIZE ][ y / CHUNK_SQUARE_SIZE ]->setTile( x % CHUNK_SQUARE_SIZE, y % CHUNK_SQUARE_SIZE, z, tilePtr );
    }

    inline void dropTile(int x, int y, bool z){
        chunks[ x / CHUNK_SQUARE_SIZE ][ y / CHUNK_SQUARE_SIZE ]->dropTile( x % CHUNK_SQUARE_SIZE, y % CHUNK_SQUARE_SIZE, z);
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
        position.x = roundf(roundf(position.x * TILE_SIZE) / TILE_SIZE);
        position.y = roundf(roundf(position.y * TILE_SIZE) / TILE_SIZE);
        return position;
    }

    void focusBlock(Vector2D position, const SDL_Color &color = {0,0,0,0});
    

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
