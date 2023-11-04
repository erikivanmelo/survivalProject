#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdint>

#define METER_TO_PIXEL(meter) meter*16 // 16 pixels = 1 meter

#define GRAVITY 9.81f/5 // m/s^2

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
    RigidBody(bool withLastState = true)
    {
        setGravity(GRAVITY);
        friction = 0;
        acceleration = 0;
        if (withLastState)
            lastState = new RigidBody(false);
    }

    void update( const RigidBody *other ) {
        gravity = other->gravity;
        acceleration = other->acceleration;
        force = other->force;
        friction = other->friction;
        position = other->position;
        velocity = other->velocity;
    }

    ~RigidBody(){
        delete lastState;
    }


    inline void setGravity( float newGravity ){ gravity = METER_TO_PIXEL(newGravity); }
    inline float getGravity ()                 const{ return gravity; }

    //Force
    inline void ApplyForces( Vector2D f ){ force   = METER_TO_PIXEL(f);  }
    inline void ApplyForceX( float fx   ){ force.x = METER_TO_PIXEL(fx); }
    inline void ApplyForceY( float fy   ){ force.y = METER_TO_PIXEL(fy); }

    inline void unsetAcceleration  () { acceleration   = 0; }
    inline void unsetAccelerationX () { acceleration.x = 0; }
    inline void unsetAccelerationY () { acceleration.y = 0; }
    inline void setAccelerationY ( const float accelerationY ) { acceleration.y = accelerationY; }

    inline void unsetForce () { force   = 0; }
    inline void unsetForceY() { force.y = 0; }
    inline void unsetForceX() { force.x = 0; }

    //Friction
    inline void applyFriction(Vector2D fr) { friction = METER_TO_PIXEL(fr);  }
    inline void unsetFriction()            { friction = Vector2D(0, 0);     }

    //Update methods
    inline Vector2D getPosition     ()const{ return position;     }
    inline Vector2D getVelocity     ()const{ return velocity;     }
    inline Vector2D getForce        ()const{ return force;        }
    inline Vector2D getAcceleration ()const{ return acceleration; }

    inline RigidBody *getLastState()const{ return lastState; }

    void update(float dt){
        lastState->update( this );
        // Calculamos la aceleración en unidades de píxeles por segundo cuadrado
        acceleration += Vector2D( 0, gravity );
        velocity = (force + acceleration) - friction;

        // Actualizamos la velocidad en unidades de píxeles por segundo
        position = velocity * dt;
    }

private:
    float gravity;

    Vector2D acceleration;

    Vector2D force;
    Vector2D friction;

    Vector2D position;
    Vector2D velocity;
    RigidBody *lastState;

};

#endif // RIGIDBODY_H
