#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Map/GameMap.h"
#include "../Graphics/TextureManager.h"

#include <SDL3/SDL_render.h>
#include <string>

class GameObject : public IObject
{
    public:
        GameObject( const string &textureId, Vector2D position, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ):
            position( position ),
            lastPosition( position ),
            width( width ),
            height( height ),
            texture( AssetsManager::get()->getTexture(textureId) ),
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
        
        inline bool isMoved()const{ return moved; }

    protected:
        Vector2D position;
        Vector2D lastPosition;
        bool moved;
        int width,height;
        SDL_Texture *texture;
        SDL_RendererFlip flip;
        Point *origin;

};

#endif // GAMEOBJECT_H
