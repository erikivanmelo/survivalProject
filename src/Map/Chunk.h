#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <cstdint>
#include <SDL2/SDL.h>
#include <iostream>
#include "../Assets/AssetsManager.h"

#define BACKGROUND 0
#define FOREGROUND 1

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 8
#define CHUNK_DEPH 2

typedef uint32_t Tile;
typedef int16_t MapSize;
typedef int8_t  ChunkSize;


class Chunk {
public:
    //TODO para guardar la porfundida del mapa utliizar un booleano, o algo similar
    
    Chunk(MapSize x, MapSize y):
        xPosition(x), yPosition(y),tileset(AssetsManager::getInstance()->getTileset())
    {
        for( int x = 0; x < CHUNK_WIDTH; ++x ){
            for( int y = 0 ; y < CHUNK_HEIGHT; ++y ){
                tiles[x][y][FOREGROUND] = 0;
                tiles[x][y][BACKGROUND] = 0;
            }
        }
    }
    ~Chunk(){}
    
    // Métodos para agregar, eliminar y obtener elementos en el chunk (por ejemplo, bloques).
    inline void setTile( const ChunkSize x, const ChunkSize y, const ChunkSize z, const Tile tile){
        this->tiles[x][y][z] = tile;
    }

    inline void dropTile( const ChunkSize x, const ChunkSize y, const ChunkSize z){
        this->tiles[x][y][z] = 0;
    }

    inline int getTile( const ChunkSize x, const ChunkSize y, const ChunkSize z) const{
        return this->tiles[x][y][z];
    };
    
    // Método para renderizar el chunk.
    void render();


private:
    const MapSize xPosition;
    const MapSize yPosition;
    Tileset *tileset;
    
    void determineRotation( Tile *tile, SDL_RendererFlip *flip);

    std::array<std::array<std::array<Tile,CHUNK_DEPH>,CHUNK_HEIGHT>,CHUNK_WIDTH> tiles;

    void drawTile(Tile tile, ChunkSize x, ChunkSize y);
};

#endif
