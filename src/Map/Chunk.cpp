#include "Chunk.h"

#include "../Graphics/TextureManager.h"
#include <cstdint>

void Chunk::drawTile(Tile tile, ChunkSize x, ChunkSize y){
    SDL_RendererFlip flip;
    determineRotation(&tile,&flip);

    TextureManager::drawTile(
        tile, 
        (xPosition*CHUNK_WIDTH+x)*tileset->tileSize, 
        (yPosition*CHUNK_HEIGHT+y)*tileset->tileSize, 
        flip
    );
}
 
void Chunk::render()
{
    Tile frontTile;
    for( int y = 0 ; y < CHUNK_HEIGHT; ++y ){
        for( int x = 0; x < CHUNK_WIDTH; ++x ){
            frontTile = tiles[x][y][FOREGROUND];
            drawTile( (frontTile == 0? tiles[x][y][BACKGROUND] : frontTile), x, y);
        }
    }
}

void Chunk::determineRotation(Tile *tile, SDL_RendererFlip *flip)
{
    *flip = SDL_FLIP_NONE;

    // Check flags
    bool flipH = (*tile & TextureManager::TileH);
    bool flipV = (*tile & TextureManager::TileV);

    // Clear flags
    *tile &= ~(TextureManager::TileD | TextureManager::TileV | TextureManager::TileH | 0x10000000);

    // Determinar las transformaciones
    if (flipV && flipH)
        *flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    else if (flipH)
        *flip = SDL_FLIP_HORIZONTAL;
    else if (flipV)
        *flip = SDL_FLIP_VERTICAL;
}


