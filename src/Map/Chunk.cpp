#include "Chunk.h"

#include "../Graphics/TextureManager.h"
#include <cstdint>

Chunk::Chunk(MapSize x, MapSize y):
    xPosition(x), yPosition(y),tileset(AssetsManager::getInstance()->getTileset()),isOnlyAir(true)
{
    std::fill(&tiles[0][0][0], &tiles[0][0][0] + CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPH, 0);
    rect = {
        (xPosition*CHUNK_WIDTH)*tileset->tileSize,
        (yPosition*CHUNK_HEIGHT)*tileset->tileSize,
        tileset->tileSize*CHUNK_WIDTH,
        tileset->tileSize*CHUNK_HEIGHT
    };
}
 
void Chunk::render()
{
    //TextureManager::drawChunk( buffer, &rect );
    Tile tile = 0;
    SDL_RendererFlip flip;
    if( isOnlyAir )
        return;
    isOnlyAir = true;
    for(int x = 0; x < CHUNK_WIDTH; ++x){
        for(int y = 0; y < CHUNK_HEIGHT; ++y){
            tile = tiles[x][y][FOREGROUND] == 0? tiles[x][y][BACKGROUND] : tiles[x][y][FOREGROUND];
            determineRotation(&tile, &flip);
            TextureManager::drawTile(
                tile,
                rect.x+(x*tileset->tileSize), 
                rect.y+(y*tileset->tileSize),
                flip
            );
            if( tile )
                isOnlyAir = false;
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
