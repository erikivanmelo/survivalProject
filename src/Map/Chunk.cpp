#include "Chunk.h"

#include "../Graphics/TextureManager.h"
#include "../Core/Engine.h"
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <cstdint>

Chunk::Chunk(MapSize x, MapSize y):
    xPosition(x), yPosition(y),tileset(AssetsManager::getInstance()->getTileset()),buffer(nullptr)
{
    std::fill(&tiles[0][0][0], &tiles[0][0][0] + CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPH, 0);
    rect = {
        (xPosition*CHUNK_WIDTH)*tileset->tileSize,
        (yPosition*CHUNK_HEIGHT)*tileset->tileSize,
        tileset->tileSize*CHUNK_WIDTH,
        tileset->tileSize*CHUNK_HEIGHT
    };
}

void Chunk::updateBuffer( const ChunkSize x, const ChunkSize y ){

    Tile tile;
    SDL_RendererFlip flip;
    SDL_Renderer *renderer = Engine::getInstance()->getRenderer();

    tile = tiles[x][y][FOREGROUND] == 0? tiles[x][y][BACKGROUND] : tiles[x][y][FOREGROUND];
    determineRotation(&tile,&flip);
    if( tile == 0 )
        return;
    if( !buffer ){
        buffer = SDL_CreateTexture(Engine::getInstance()->getRenderer(), Assets::pixelDepth, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    }

    SDL_SetRenderTarget(renderer, buffer);
    SDL_Rect origenRect, destinoRect;
    origenRect = { 0, 0, tileset->tileSize, tileset->tileSize };
    destinoRect = { x*tileset->tileSize, y*tileset->tileSize, tileset->tileSize, tileset->tileSize };

    SDL_RenderCopyEx(renderer, tileset->textures[tile], &origenRect, &destinoRect, 0, nullptr, flip);

    if(!buffer){
        throw std::string("no se cargo :/");
    }

    // Restaurar el destino original
    SDL_SetRenderTarget(renderer, nullptr);
}
 
void Chunk::render()
{
    if( buffer )
        TextureManager::drawFrame( buffer, rect.x, rect.y, rect.w, rect.h);
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
