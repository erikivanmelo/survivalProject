#include "Chunk.h"

#include "../Graphics/TextureManager.h"
#include <cstdint>

#include <SDL3/SDL_render.h>

Chunk::Chunk(MapSize x, MapSize y):
    xPosition(x), yPosition(y),tileset(AssetsManager::getInstance()->getTileset()),isOnlyAir(true)
{
    std::fill(&tiles[0][0][0], &tiles[0][0][0] + CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPH, nullptr);
    rect = {
        (float)(xPosition*CHUNK_WIDTH)*tileset->tileSize,
        (float)(yPosition*CHUNK_HEIGHT)*tileset->tileSize,
        (float)tileset->tileSize*CHUNK_WIDTH,
        (float)tileset->tileSize*CHUNK_HEIGHT
    };
}
 
void Chunk::render()
{
    if( isOnlyAir )
        return;
    isOnlyAir = true;
    Tile backTile = 0, frontTile = 0;
    SDL_RendererFlip flip;
    ChunkSize x,y;
    for(x = 0; x < CHUNK_WIDTH; ++x){
        for(y = 0; y < CHUNK_HEIGHT; ++y){
            frontTile = tiles[x][y][FOREGROUND] ? determineRotation(tiles[x][y][FOREGROUND], &flip) : 0;
            backTile  = !frontTile              ? determineRotation(tiles[x][y][BACKGROUND], &flip) : 0;
            if( !frontTile && !backTile )
                continue;
            isOnlyAir = false;
            TextureManager::draw(
                tileset->textures[backTile? backTile : frontTile],
                rect.x+(x*tileset->tileSize),
                rect.y+(y*tileset->tileSize),
                tileset->tileSize,
                tileset->tileSize,
                flip,
                backTile? 85 : 0
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
