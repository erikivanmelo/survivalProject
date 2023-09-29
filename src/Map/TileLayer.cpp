#include "TileLayer.h"
//#include "Camera/camera.h"

#include "../Graphics/TextureManager.h"


TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, Tileset tileset):
    tileSize(tilesize),rowCount(rowcount),colCount(colcount),tileMap(tilemap),tileset(tileset)
{
    if( !TextureManager::getInstance()->load(tileset.name,tileset.source) )
        exit(1);
}

void TileLayer::render()
{
    unsigned int tileId;
    SDL_RendererFlip flip;
    int tileRow,tileCol;

    //SDL_Rect box = Camera::getInstance()->getViewBox();

    for(int row = 0 ; row < rowCount; row++){
        for(int col = 0; col < colCount; col++){
            // si el bloque es de aire se saltea el dibujado
            if( ( tileId = tileMap[row][col] ) == 0)
                continue;

            determineRotation(tileId,flip);
        
            tileRow = tileId / tileset.colCount;
            tileCol = tileId - tileRow*tileset.colCount-1;

            if(tileId % tileset.colCount == 0){
                tileRow--;
                tileCol = tileset.colCount -1;
            }

            TextureManager::getInstance()->drawTile(tileset.name, tileset.tileSize, col*tileset.tileSize, row*tileset.tileSize,tileRow,tileCol,flip);
        }
    }
}

void TileLayer::determineRotation(unsigned int& tileId, SDL_RendererFlip& flip)
{
    flip = SDL_FLIP_NONE;

    // Check flags
    bool flipH = (tileId & TextureManager::TileH);
    bool flipV = (tileId & TextureManager::TileV);

    // Clear flags
    tileId &= ~(TextureManager::TileD | TextureManager::TileV | TextureManager::TileH | 0x10000000);

    // Determinar las transformaciones
    if (flipV && flipH)
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    else if (flipH)
        flip = SDL_FLIP_HORIZONTAL;
    else if (flipV)
        flip = SDL_FLIP_VERTICAL;
}

