#ifndef TRANSFORH
#define TRANSFORH

#include "Vector2D.h"

class Transform
{

    public:
        float x,y;

    public:
        Transform(float X = 0, float Y = 0):x(X),y(Y){};

        void log(const std::string &msg = ""){
            std::cout << msg << "(X, Y) = (" << x << " " << y << ")" << std::endl;
        }

    public:
        inline void translateX(float x){this->x += x;}
        inline void translateY(float y){this->y += y;}
        inline void translate(Vector2D v){this->x += v.x;this->y += v.y;}


};

#endif // TRANSFORH
