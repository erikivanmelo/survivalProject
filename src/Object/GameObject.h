#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

#include "../Physics/Transform.h"
#include "../Physics/Point.h"

#include <SDL2/SDL_render.h>
#include <string>

struct Properties{

public:
    Properties( const std::string &TextureId, int X, int Y, int Width, int Height,SDL_RendererFlip Flip = SDL_FLIP_NONE ): textureId(TextureId), x(X), y(Y), width(Width), height(Height), flip(Flip){
    }

    const std::string textureId;
    float x,y;
    int width,height;
    SDL_RendererFlip flip;

};

class GameObject : public IObject
{
    public:
        GameObject( Properties *props ) : 
            width( props->width ),
            height( props->height ),
            textureId( props->textureId ),
            flip( props->flip )
        {
            transform = new Transform( props->x, props->y );

            origin = new Point(
                props->x + (int)(props->width/2),
                props->y + (int)(props->height/2)
            );
        }

        ~GameObject(){
            delete transform;
            delete origin;
        }

        void updateViewPoint(){
            origin->x = transform->x + (int)(width/2);
            origin->y = transform->y + (int)(height/2);
        }

        void update(float dt){
            updateViewPoint();
        }

        inline Point *getOrigin(){return origin;}


    protected:
        Point *origin;
        Transform *transform;
        int width,height;
        std::string textureId;
        SDL_RendererFlip flip;

};

#endif // GAMEOBJECT_H



