#ifndef POINT_H
#define POINT_H


#include <iostream>
class Point
{
public:
    float x,y;

    Point(float X, float Y):x(X),y(Y){}

    //Adition
    inline Point operator+(const Point &p2) const{
        return Point(x + p2.x, y + p2.y);
    }

    //Adition
    inline friend Point operator+=(Point p1, Point p2){
        p1.x += p2.x;
        p1.y += p2.y;
        return p1;
    }

    //Substraction
    inline Point operator-(const Point &p2) const{
        return Point(x - p2.x, y - p2.y);
    }

    //substraction
    inline friend Point operator-=(Point p1, Point p2){
        p1.x -= p2.x;
        p1.y -= p2.y;
        return p1;
    }

    inline Point operator*(const float scalar) const{
        return Point(x*scalar,y*scalar);
    }

    void log(const std::string &msg = "")const{
        std::cout << msg << "(x,y) = ("<< x << " " << y <<")"<<std::endl;
    }

};

#endif // POINT_H
