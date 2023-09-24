#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

#include "../Physics/Transform.h"
#include "../Physics/Point.h"

#include <SDL2/SDL_render.h>
#include <string>

struct Properties{

public:
    Properties( std::string TextureId, int X, int Y, int Width, int Height,SDL_RendererFlip Flip = SDL_FLIP_NONE ){
        x = X;
        y = Y;
        width = Width;
        height = Height;
        flip = Flip;
        textureId = TextureId;
    }

    std::string textureId;
    int width,height;
    float x,y;
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
                props->x + props->width/2,
                props->y + props->height/2
            );
        }

        inline Point *getOrigin(){return origin;}

        virtual void draw()=0;
        virtual void update(float dt)=0;

    protected:
        Point *origin;
        Transform *transform;
        int width,height;
        std::string textureId;
        SDL_RendererFlip flip;

};

#endif // GAMEOBJECT_H



