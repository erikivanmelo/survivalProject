#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<SDL3/SDL_rect.h>

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 300
#define DEFAULT_SCREEN_SCALE 2

#define DIRECTION_UP -1
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1

#define BACKGROUND 0
#define FOREGROUND 1

#define TILE_SIZE 8

#define CHUNK_SQUARE_SIZE 8
#define CHUNK_PIXEL_SQUARE_SIZE CHUNK_SQUARE_SIZE*TILE_SIZE
#define CHUNK_DEPH 2


namespace Helper{

    inline int wrapToRange(const int value, const int max, const int margin = 0){
        return (value + max+margin) % max-margin;
    }

    inline void printRect( SDL_FRect rect , const std::string &nombre = "" ) {
        std ::cout << nombre << ": x:" << rect.x << " - y:" << rect.y << " - w:" << rect.w << " - h:" << rect.h << std::endl;
    }

};
#endif
