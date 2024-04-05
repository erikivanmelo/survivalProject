#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Object/IObject.h"
#include "../Physics/Vector2D.h"

#include <SDL3/SDL_render.h>
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>
using namespace std;

struct AnimationSeq{
    AnimationSeq(
        SDL_Texture *texture,
        const uint8_t spriteRow,
        const uint8_t frameCount, 
        const uint8_t animSpeed,
        const uint8_t spriteWidth,
        const uint8_t spriteHeight
    ):
        texture(texture),
        spriteRow(spriteRow),
        frameCount(frameCount),
        animSpeed(animSpeed),
        spriteWidth(spriteWidth),
        spriteHeight(spriteHeight)
    {}

    SDL_Texture *texture;
    const uint8_t spriteRow;
    const uint8_t frameCount;
    const uint8_t animSpeed;
    const uint8_t spriteWidth;
    const uint8_t spriteHeight;
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
typedef pair<const string, AnimationSeq* > AnimationSeqPair;

class Animation : public IObject
{
public:
    Animation(AnimationSeqList *list, Vector2D *position);
    ~Animation();
    void update(float dt) override;
    void draw() override;
    void debug() override{};
    void setCurrentSeq( const string &seqId, SDL_RendererFlip flip = SDL_FLIP_NONE, const uint8_t animSpeed = 0);

private:
    SDL_RendererFlip flip;
    AnimationSeqList *seqList;
    AnimationSeq* currentSeq;
    
    uint8_t forceAnimSpeed;
    uint8_t spriteFrame;
    Vector2D *position;
};

#endif // ANIMATION_H
