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
    RigidBody():
        gravity(Vector2D( 0, METER_TO_PIXEL(GRAVITY))),
        friction(0),
        position(0),
        velocity(0),
        movement(0)
    {}

    inline void setGravity( float newGravity ){ gravity = Vector2D( 0, METER_TO_PIXEL(newGravity) ); }
    inline float getGravity ()                 const{ return gravity.y; }

    //Velocity
    inline void setVelocity ( Vector2D f ){ velocity = METER_TO_PIXEL(f);  }
    inline void setVelocityX( float fx   ){ velocity.x = METER_TO_PIXEL(fx); }
    inline void setVelocityY( float fy   ){ velocity.y = METER_TO_PIXEL(fy); }

    inline void applyMovement ( Vector2D f ){ movement   = METER_TO_PIXEL(f);  }
    inline void applyMovementX( float fx   ){ movement.x = METER_TO_PIXEL(fx); }
    inline void applyMovementY( float fy   ){ movement.y = METER_TO_PIXEL(fy); }

    //Friction
    inline void applyFriction(Vector2D fr) { friction = METER_TO_PIXEL(fr);  }
    inline void unsetFriction()            { friction = Vector2D(0, 0);     }

    //Update methods
    inline Vector2D getPosition     ()const{ return position;     }
    inline Vector2D getVelocity     ()const{ return velocity;     }

    inline void unsetVelocity()            { velocity = Vector2D(0, 0);     }
    inline void unsetVelocityX()           { velocity.x = 0;     }
    inline void unsetVelocityY()           { velocity.y = 0;     }

    void update(float dt){

        velocity += gravity - friction;
        //velocity.log("velocity");

        // Actualizamos la velocidad en unidades de píxeles por segundo
        position = (velocity + movement) * dt;
        movement = Vector2D(0,0);
    }

private:
    Vector2D gravity;

    Vector2D friction;

    Vector2D position;
    Vector2D velocity;
    Vector2D movement;

};

#endif // RIGIDBODY_H
