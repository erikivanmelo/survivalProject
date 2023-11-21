#include "AssetsManager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include "../Core/Engine.h"

AssetsManager* AssetsManager::instance = nullptr;

SDL_Texture *AssetsManager::loadTexture( 
        const string &id,
        const string &fileName, 
        const bool withTransparentMagenta, 
        const bool saveIt, 
        const SDL_Rect srcRect
    ){

    SDL_Surface* surface = SDL_LoadBMP( fileName.c_str() );
    if( !surface )
        throw "Failed to load image " + fileName + "! SDL_image Error: " + string(SDL_GetError());

    SDL_Texture* texture    = nullptr;
    SDL_Surface* newSurface = nullptr;

    surface = SDL_ConvertSurfaceFormat(surface, Assets::pixelDepth);

    // Añade el color magenta a la lista de colores transparentes.
    if( withTransparentMagenta )
        SDL_SetSurfaceColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255 ));

    if( srcRect.w > 0 && srcRect.h > 0 ){
        newSurface = SDL_CreateSurface(srcRect.w, srcRect.h, Assets::pixelDepth);
        if( !newSurface )
            throw "Failed to load surface from" + fileName + "! SDL_image Error: " + string(SDL_GetError());
        SDL_SetSurfaceColorKey(newSurface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255 ));
        SDL_BlitSurface(surface, &srcRect, newSurface, nullptr);
        // Crea una textura a partir de la nueva superficie.
        texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), newSurface);
    }else{
        texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
    }
    
    if ( !texture )
        throw "Failed to create texture from " + fileName + "! SDL Error: " + string(SDL_GetError());

    SDL_DestroySurface(surface);
    if(newSurface)
        SDL_DestroySurface(newSurface);

    if( saveIt )
        this->textureMap[id] = texture;
    return texture;
}

void AssetsManager::load(){
    // Abrir el archivo JSON en modo lectura
    std::ifstream file(Assets::base + "sprites.json");

    // Comprobar si se pudo abrir el archivo
    if (!file.is_open()) 
        throw "No se pudo abrir el archivo de configuracion de los sprites.";

    // Crear un objeto JSON para almacenar los datos
    nlohmann::json jsonData;

    // Leer el archivo JSON en el objeto JSON
    file >> jsonData;

    // Cerrar el archivo
    file.close();

    // Acceder a los datos del archivo JSON
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        nlohmann::json spriteData = it.value();

        string fileName = it.key();
        string name = fileName.substr( 0, fileName.find_last_of('.') );
        int width = spriteData["width"], height = spriteData["height"];

        SDL_Texture *texture = this->loadTexture(
            name,
            Assets::sprites + fileName,
            spriteData["withTransparentMagenta"]
        );

        // Acceder a "animationSeqs"
        if( !spriteData["animationSeqs"].empty() ){
            nlohmann::json seqsData = spriteData["animationSeqs"];

            AnimationSeqList *animationSeqs = new AnimationSeqList();
            for (auto seq = seqsData.begin(); seq != seqsData.end(); ++seq) {
                nlohmann::json seqData = seq.value(); 

                animationSeqs->insert(
                    seq.key(), 
                    new AnimationSeq(
                        texture, 
                        seqData["row"], 
                        seqData["count"], 
                        seqData["speed"], 
                        width, height 
                    ) 
                );
            }
            if( !animationSeqs->exist("default")  )
                animationSeqs->insert( "default", new AnimationSeq(texture, 1, 1, 0, width, height) );
            this->animationSeqMap[name] = animationSeqs;
        }

    }

}

