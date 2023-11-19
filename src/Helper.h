#include<iostream>
#include<SDL3/SDL_rect.h>

namespace Helper{

    inline int wrapToRange(const int value, const int max){
        return (value + max) % max;
    }

    inline void printRect( SDL_FRect rect , const std::string &nombre = "" ) {
        std ::cout << nombre << ": x:" << rect.x << " - y:" << rect.y << " - w:" << rect.w << " - h:" << rect.h << std::endl;
    }

};
