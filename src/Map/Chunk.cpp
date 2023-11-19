#include "Chunk.h"

#include "../Graphics/TextureManager.h"
#include <cstdint>

Chunk::Chunk(MapSize x, MapSize y):
    xPosition(x), yPosition(y),tileset(AssetsManager::getInstance()->getTileset()),isOnlyAir(true)
{
    std::fill(&tiles[0][0][0], &tiles[0][0][0] + CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPH, nullptr);
    rect = {
        (xPosition*CHUNK_WIDTH)*tileset->tileSize,
        (yPosition*CHUNK_HEIGHT)*tileset->tileSize,
        tileset->tileSize*CHUNK_WIDTH,
        tileset->tileSize*CHUNK_HEIGHT
    };
}
 
void Chunk::render()
{
    if( isOnlyAir )
        return;
    isOnlyAir = true;
    Tile *tile = nullptr;
    Tile tmpTile = 0;
    SDL_RendererFlip flip;
    ChunkSize x,y;
    for(x = 0; x < CHUNK_WIDTH; ++x){
        for(y = 0; y < CHUNK_HEIGHT; ++y){
            tile = tiles[x][y][FOREGROUND]? tiles[x][y][FOREGROUND] : tiles[x][y][BACKGROUND];
            if( !(tmpTile = determineRotation(tile, &flip)) )
                continue;
            isOnlyAir = false;
            TextureManager::drawTile(
                tmpTile,
                rect.x+(x*tileset->tileSize), 
                rect.y+(y*tileset->tileSize),
                flip
            );
        }
    }
}

Tile Chunk::determineRotation(Tile *tile, SDL_RendererFlip *flip)
{
    if( !tile )
        return 0;
    *flip = SDL_FLIP_NONE;
    Tile tmp = *tile;
    // Check flags
    bool flipH = (*tile & TextureManager::TileH);
    bool flipV = (*tile & TextureManager::TileV);

    // Clear flags
    tmp &= ~(TextureManager::TileD | TextureManager::TileV | TextureManager::TileH | 0x10000000);

    // Determinar las transformaciones
    if (flipV && flipH)
        *flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    else if (flipH)
        *flip = SDL_FLIP_HORIZONTAL;
    else if (flipV)
        *flip = SDL_FLIP_VERTICAL;
    return tmp;
}
