#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Map/GameMap.h"
#include "../Graphics/TextureManager.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <string>

class GameObject : public IObject
{
    public:
        GameObject( const string &textureId, Vector2D position, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ):
            position( position ),
            width( width ),
            height( height ),
            texture( AssetsManager::getInstance()->getTexture(textureId) ),
            flip( flip ),
            origin(new Point(
                position.x + (int)( width/2  ),
                position.y + (int)( height/2 )
            ))
        {}

        ~GameObject(){
            delete origin;
        }

        inline void updateViewPoint(){
            origin->x = position.x + (int)(width/2);
            origin->y = position.y + (int)(height/2);
        }

        void update(float dt) override;

        inline Point *getOrigin(){return origin;}

        inline Vector2D getPosition()const{ return position; }

    protected:
        Vector2D position;
        int width,height;
        SDL_Texture *texture;
        SDL_RendererFlip flip;
        Point *origin;

};

#endif // GAMEOBJECT_H