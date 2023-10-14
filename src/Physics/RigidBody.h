#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdint>

#define METER_TO_PIXEL 16 // 16 pixels = 1 meter

#define UNIT_MASS 1.0f

#define GRAVITY 9.81f // m/s^2

namespace MoveDirection{
    constexpr int8_t UP = -1;
    constexpr int8_t DOWN = 1;
    constexpr int8_t LEFT = -1;
    constexpr int8_t RIGHT = 1;
}

enum MoveOption{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class RigidBody
{
public:
    RigidBody(){
        setGravity(GRAVITY);
        applyFriction(0);
    }


    inline void setMass   ( float newMass    ){ mass = newMass;       }
    inline void setGravity( float newGravity ){ gravity = newGravity*METER_TO_PIXEL; }

    //Force
    inline void ApplyForces( Vector2D f ){ force   = f*METER_TO_PIXEL;  }
    inline void ApplyForceX( float fx   ){ force.x = fx*METER_TO_PIXEL; }
    inline void ApplyForceY( float fy   ){ force.y = fy*METER_TO_PIXEL; }
    inline void unsetForce()             { force   = Vector2D(0,0);     }

    //Friction
    inline void applyFriction(Vector2D fr) { friction = fr*METER_TO_PIXEL;  }
    inline void unsetFriction()            { friction = Vector2D(0, 0);     }

    //Update methods
    inline float    getMass        ()const{ return mass;        }
    inline Vector2D getPosition    ()const{ return position;    }
    inline Vector2D getVelocity    ()const{ return velocity;    }
    inline Vector2D getAcceleration()const{ return acceleration;}

    void update(float dt){

        // Calculamos la aceleración en unidades de píxeles por segundo cuadrado
        acceleration = (force + Vector2D(0,gravity)) - friction;

        // Actualizamos la velocidad en unidades de píxeles por segundo
        position = velocity = acceleration * dt;
    }

private:
    float mass;
    float gravity;

    Vector2D force;
    Vector2D friction;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
};

#endif // RIGIDBODY_H
