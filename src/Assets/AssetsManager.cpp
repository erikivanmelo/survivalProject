#include "AssetsManager.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "../Core/Engine.h"

AssetsManager* AssetsManager::instance = nullptr;

SDL_Texture *AssetsManager::loadTexture( const string &id, const string &fileName, bool withTransparentMagenta, const bool saveIt, const int x, const int y, const int width, const int height){    
    SDL_Surface* surface = IMG_Load( fileName.c_str() );
    SDL_Surface* newSurface = nullptr;
    if( !surface )
        throw "Failed to load image " + fileName + "! SDL_image Error: " + string(IMG_GetError());
    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC);
    SDL_Texture* texture;
    // Añade el color magenta a la lista de colores transparentes.
    if( withTransparentMagenta)
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255 ));

    if( width > 0 && height > 0){
        cout << "x:" << x << "-y:" << y << endl;

        newSurface = SDL_CreateRGBSurface(0, width, height, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

        SDL_Rect sourceRect = {x, y, width, height};
        SDL_BlitSurface(surface, &sourceRect, newSurface, NULL);
        // Crea una textura a partir de la nueva superficie.
        texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), newSurface);
    }else{
        texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
    }
    
    if ( !texture )
        throw "Failed to create texture from " + fileName + "! SDL Error: " + string(SDL_GetError());


    SDL_FreeSurface(surface);
    if(newSurface)
        SDL_FreeSurface(newSurface);

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

