#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

#include <string>

#include <SDL2/SDL.h>
#include <unordered_map>

struct AnimationSeq{
    AnimationSeq(
        SDL_Texture *texture,
        int spriteRow,
        int frameCount, 
        int animSpeed,
        int spriteWidth,
        int spriteHeight
    ):
        texture(texture),
        spriteRow(spriteRow),
        frameCount(frameCount),
        animSpeed(animSpeed),
        spriteWidth(spriteWidth),
        spriteHeight(spriteHeight)
    {}

    SDL_Texture *texture;
    int spriteRow;
    int frameCount;
    int animSpeed;
    int spriteWidth;
    int spriteHeight;
};

class AnimationSeqList{

public:
    AnimationSeqList(){}
    ~AnimationSeqList(){
        auto it = list.begin();
        while (it != list.end()) {
            delete it->second;
        }
    }

    AnimationSeq* operator[](const string &index) {
        return list[index];
    }

    void insert(const string &key, AnimationSeq *value ){
        list[key] = value;
    }

    AnimationSeq* at( const string &key ){
        return list[key];
    }


    bool exist(const string &id){
        return list.count(id) > 0;
    }
    
private:
    unordered_map< string, AnimationSeq* > list;
};

typedef struct AnimationSeq AnimationSeq;
//typedef unordered_map< string, AnimationSeq* > AnimationSeqList;
typedef pair< string, AnimationSeq* > AnimationSeqPair;

class Animation
{
public:
    Animation( AnimationSeqList *list );
    ~Animation();
    void update();
    void draw( float x, float y );
    void setCurrentSeq( const string &seqId, SDL_RendererFlip flip = SDL_FLIP_NONE, int animSpeed = -1 );

private:
    SDL_RendererFlip flip;
    AnimationSeqList *seqList;
    AnimationSeq* currentSeq;
    int forceAnimSpeed;
    int spriteFrame;
};

#endif // ANIMATION_H
