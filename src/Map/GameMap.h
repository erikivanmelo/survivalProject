#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <iostream>
#include <vector>
#include "Chunk.h"

typedef std::vector<std::vector<Chunk*>> ChunkList;

class GameMap
{
public:
    GameMap( const MapSize width, const MapSize height ):
        chunkWidth(width), chunkHeight(height),
        pixelWidth((width*CHUNK_WIDTH)*AssetsManager::getInstance()->getTileset()->tileSize),
        pixelHeight((height*CHUNK_HEIGHT)*AssetsManager::getInstance()->getTileset()->tileSize),
        tileWidth(width*CHUNK_WIDTH),
        tileHeight(height*CHUNK_HEIGHT)
    {

        chunks.resize(width);
        for (MapSize i = 0; i < width; ++i) {
            chunks[i].resize(height);
        }

        for (int x = 0; x < chunkWidth; ++x) {
            for (int y = 0; y < chunkHeight; ++y) {
                chunks[x][y] = new Chunk(x,y);
            } 
        }
    }

    ~GameMap(){
        const ChunkSize xCount = chunks.size(), yCount = chunks[0].size();
        for (int x = 0; x < xCount; ++x) {
            for (int y = 0; y < yCount; ++y) {
                delete chunks[x][y];
                chunks[x][y] = nullptr;
            }
            chunks[x].clear();
        }
        chunks.clear();
    }

    void render(){
        for (int x = 0; x < chunkWidth; ++x) {
            for (int y = 0; y < chunkHeight; ++y) {
                chunks[x][y]->render();
            } 
        }
    }

    void update(){}

    Chunk* getChunk(MapSize x, MapSize y)const{
        return chunks[x][y];
    }

    Tile getTile(int x, int y, int z = FOREGROUND)const{
        return chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->getTile( x%8, y%8, z);
    }

    void setTile(int x, int y, int z, Tile tile){
        //cout << "chX:" << x / CHUNK_WIDTH << " - chY:" << y / CHUNK_HEIGHT << " - tileX:" << x % CHUNK_HEIGHT << " - tileY" << y%CHUNK_HEIGHT << endl; 
        chunks[ x / CHUNK_WIDTH ][ y / CHUNK_HEIGHT ]->setTile( x%CHUNK_WIDTH, y%CHUNK_HEIGHT, z, tile );
    }


    //TODO re ver los nombres para retornar el tamaño del mapa en distintas unidades
    MapSize getChunkHeight() const{
        return chunkHeight;
    }

    MapSize getChunkWidth()const{
        return chunkWidth;
    }

    int getPixelHeight() const{
        return pixelHeight;
    }

    int getPixelWidth()const{
        return pixelWidth;
    }

    int getTileHeight() const{
        return tileHeight;
    }

    int getTileWidth()const{
        return tileWidth;
    }
    Tileset tileset;

private:
    friend class MapParser;
    ChunkList chunks;
    const MapSize chunkWidth, chunkHeight;
    const int     pixelWidth, pixelHeight;
    const int     tileWidth,  tileHeight;

};

#endif // GAMEMAP_H
