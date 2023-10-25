#include "TileLayer.h"
#include "../Camera/Camera.h"

#include "../Graphics/TextureManager.h"
#include "../Assets/AssetsManager.h"


TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, Tileset tileset):
    tileSize(tilesize),
    rowCount(rowcount),
    colCount(colcount),
    width(colcount*tilesize),
    height(rowcount*tilesize),
    tileMap(tilemap),
    tileset(tileset)
{
    AssetsManager::getInstance()->loadTexture(tileset.name,tileset.source,true);
}

void TileLayer::render()
{
    unsigned int tileId;
    SDL_RendererFlip flip;
    int tileRow,tileCol;

    SDL_Rect box = Camera::getInstance()->getViewBox();

    
    for( int row = 0 ; row < rowCount; row++ ){
        for( int col = box.x / tileSize; col < (box.x+box.w) / tileSize; col++ ){
            //Guarda el tile de la coordenada actual. En caso de sea menor que cero toma el ultimot bloque del mapa y en caso de que sea mayor que cero toma el primero
            // si el bloque es de aire se saltea el dibujado
            if( ( tileId = tileMap[row][ ( col % colCount + colCount ) % colCount] ) == 0)
                continue;

            determineRotation(tileId,flip);
        
            tileRow = tileId / tileset.colCount;
            tileCol = tileId - tileRow*tileset.colCount-1;

            if( !(tileId % tileset.colCount) ){
                tileRow--;
                tileCol = tileset.colCount -1;
            }

            TextureManager::drawTile(
                tileset.name, 
                tileset.tileSize, 
                col * tileset.tileSize, 
                row * tileset.tileSize,
                tileRow,
                tileCol,
                flip
            );

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

