#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <cstdint>

#define METER_TO_PIXEL(meter) meter*16 // 16 pixels = 1 meter

#define GRAVITY 9.81f // m/s^2


#define OPTION_UP 0
#define OPTION_DOWN 1
#define OPTION_LEFT 2
#define OPTION_RIGHT 3

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

        velocity += ((gravity*10) - friction)*dt;

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
