#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Map/GameMap.h"
#include "../Core/Engine.h"


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
            position( props->x, props->y ),
            width( props->width ),
            height( props->height ),
            textureId( props->textureId ),
            flip( props->flip )
        {

            origin = new Point(
                props->x + (int)(props->width/2),
                props->y + (int)(props->height/2)
            );
        }

        ~GameObject(){
            delete origin;
        }

        void updateViewPoint(){
            origin->x = position.x + (int)(width/2);
            origin->y = position.y + (int)(height/2);
        }

        void update(float dt) override{
            static const float widthMap = Engine::getInstance()->getMap()->getMapLayers()[GameMap::foreground]->getColCount() * GameMap::blockSize;

            if (position.x > widthMap) 
                position.x = fmod(position.x, widthMap);
            else if (position.x < 0)
                position.x = widthMap + fmod(position.x, widthMap);

            updateViewPoint();
        }

        inline Point *getOrigin(){return origin;}

        inline Vector2D getPosition()const{ return position; }

    protected:
        Point *origin;
        Vector2D position;
        int width,height;
        std::string textureId;
        SDL_RendererFlip flip;

};

#endif // GAMEOBJECT_H



