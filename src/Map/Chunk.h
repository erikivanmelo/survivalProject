#ifndef CHUNK_H
#define CHUNK_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
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
    
    Chunk(MapSize x, MapSize y);

    ~Chunk(){
    }
    
    // Métodos para agregar, eliminar y obtener elementos en el chunk (por ejemplo, bloques).
    inline void setTile( const ChunkSize x, const ChunkSize y, const ChunkSize z, const Tile tile){
        this->tiles[x][y][z] = tile;
        if( tile )
            isOnlyAir = false;
    }

    inline void dropTile( const ChunkSize x, const ChunkSize y, const ChunkSize z){
        setTile( x, y, z, 0);
    }

    inline int getTile( const ChunkSize x, const ChunkSize y, const ChunkSize z) const{
        return this->tiles[x][y][z];
    };
    
    // Método para renderizar el chunk.
    void render();


private:
    const MapSize xPosition;
    const MapSize yPosition;
    SDL_Rect rect;
    Tileset *tileset;
    bool isOnlyAir;
    
    void determineRotation( Tile *tile, SDL_RendererFlip *flip);

    std::array<std::array<std::array<Tile,CHUNK_DEPH>,CHUNK_HEIGHT>,CHUNK_WIDTH> tiles;

    void drawBuffer(Tile tile, ChunkSize x, ChunkSize y);
};

#endif
