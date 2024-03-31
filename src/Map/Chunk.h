#ifndef CHUNK_H
#define CHUNK_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <array>
#include <cstdint>
#include <SDL3/SDL.h>
#include "../Assets/AssetsManager.h"
#include "../Helper.h"

typedef uint32_t Tile;
typedef int16_t MapSize;
typedef int_fast8_t  ChunkSize;

class GameMap;
class Chunk {
public:
    
    Chunk(MapSize x, MapSize y);

    ~Chunk(){
    }
    
private:
    friend class GameMap;
    // Métodos para agregar, eliminar y obtener elementos en el chunk (por ejemplo, bloques).
    inline void setTile( const ChunkSize x, const ChunkSize y, const bool z, Tile *tile){
        if( (this->tiles[x][y][z] = tile) )
            isOnlyAir = false;
    }

    inline void dropTile( const ChunkSize x, const ChunkSize y, const bool z){
        setTile( x, y, z, nullptr);
    }

    inline Tile *getTile( const ChunkSize x, const ChunkSize y, const bool z) const{
        return this->tiles[x][y][z];
    };
    
    // Método para renderizar el chunk.
    void render();


    const MapSize xPosition;
    const MapSize yPosition;
    SDL_FRect rect;
    Tileset *tileset;
    bool isOnlyAir;
    
    Tile determineRotation( Tile *tile, SDL_RendererFlip *flip);

    std::array<std::array<std::array<Tile*,CHUNK_DEPH>,CHUNK_SQUARE_SIZE>,CHUNK_SQUARE_SIZE> tiles;
};

#endif
