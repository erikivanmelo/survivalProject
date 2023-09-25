#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <string>

class Vector2D
{

public:
    float x, y;

public:
    Vector2D( float X=0, float Y=0 ):x(X),y(Y){}

public:
    inline Vector2D operator+(const Vector2D& v2){
        return Vector2D( x+v2.x, y+v2.y );
    }

    inline Vector2D operator-(const Vector2D& v2){
        return Vector2D( x-v2.y, y-v2.y );
    }

    inline Vector2D operator*(const float scalar){
        return Vector2D( x*scalar, y*scalar );
    }

    inline Vector2D operator/(const float scalar){
        return Vector2D( x/scalar, y/scalar );
    }


    void log(std::string msg = ""){
        std::cout << msg << "(X, Y) = (" << x << " " << y << ")" << std::endl;
    }

};

#endif // VECTOR2D_H

