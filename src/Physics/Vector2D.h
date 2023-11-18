#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
#include <string>

class Vector2D
{

public:
    float x, y;

    Vector2D( float X=0, float Y=0 ):x(X),y(Y){}

    inline Vector2D operator+(const Vector2D& v2){
        return Vector2D( this->x + v2.x, this->y + v2.y );
    }

    Vector2D operator+=(const Vector2D& v2){
        this->x = this->x + v2.x;
        this->y = this->y + v2.y;
        return *this;
    }

    Vector2D operator-=(const Vector2D& v2){
        this->x = this->x - v2.x;
        this->y = this->y - v2.y;
        return *this;
    }

    
    bool operator<(const Vector2D& v2){
        return ( this->x < v2.x && this->y < v2.y);
    }

    bool operator<(const float& v2){
        return ( this->x < v2 && this->y < v2);
    }

    bool operator!=(const float& v2){
        return ( this->x != v2 && this->y != v2);
    }

    bool operator!=(const Vector2D& v2){
        return ( this->x != v2.x && this->y != v2.y);
    }

    bool operator==(const Vector2D& v2){
        return ( this->x == v2.x && this->y == v2.y);
    }

    bool operator<(const int& v2){
        return ( this->x < v2 && this->y < v2);
    }

    inline Vector2D operator-(const Vector2D& v2){
        return Vector2D( this->x - v2.x, this->y - v2.y );
    }

    inline Vector2D operator*(const float scalar){
        return Vector2D( this->x * scalar, this->y * scalar );
    }

    inline Vector2D operator/(const float scalar){
        return Vector2D( this->x / scalar, this->y / scalar );
    }

    inline float length(){ return  (float)std::sqrt(x * x + y * y); }
    Vector2D normalize(){ 
        float l = length();
        return l > 0 ? Vector2D(x / l, y / l) : Vector2D(0, 0);
    }


    void log(const std::string &msg = "")const{
        std::cout << msg << "(X, Y) = (" << x << " " << y << ")" << std::endl;
    }

};

#endif // VECTOR2D_H

