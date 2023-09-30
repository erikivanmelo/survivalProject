#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"
#include <SDL2/SDL.h>

#define METER_TO_PIXEL 16 // 16 pixels = 1 meter
#define PIXEL_TO_METER (1.0f / METER_TO_PIXEL)

#define UNIT_MASS 1.0f

#define GRAVITY 9.81f // m/s^2

class RigidBody
{
public:
    RigidBody(){
        mass = UNIT_MASS;
        gravity = GRAVITY;
    }


    inline void setMass   ( float newMass    ){ mass = newMass;       }
    inline void setGravity( float newGravity ){ gravity = newGravity; }

    //Force
    inline void ApplyForces( Vector2D f ){ force = f;             }
    inline void ApplyForceX( float fx   ){ force.x = fx;          }
    inline void ApplyForceY( float fy   ){ force.y = fy;          }
    inline void unsetForce()             { force = Vector2D(0,0); }

    //Friction
    inline void ApplyFriction(Vector2D fr) { friction = fr;             }
    inline void unsetFriction()            { friction = Vector2D(0, 0); }

    //Update methods
    inline float    getMass        ()const{ return mass;        }
    inline Vector2D getPosition    ()const{ return position;    }
    inline Vector2D getVelocity    ()const{ return velocity;    }
    inline Vector2D getAcceleration()const{ return acceleration;}

    void update(float dt){
        dt *= 100; //para que el calculo lo haga por segundo
        // Convertimos las fuerzas a unidades de píxeles por segundo
        Vector2D forceInPixels = force * METER_TO_PIXEL;
        Vector2D frictionInPixels = friction * METER_TO_PIXEL;
        Vector2D gravityInPixels = Vector2D(0, gravity) * METER_TO_PIXEL;

        // Calculamos la aceleración en unidades de píxeles por segundo cuadrado
        acceleration = ( gravity == 0? forceInPixels : (forceInPixels + gravityInPixels - frictionInPixels )) / mass;

        // Actualizamos la velocidad en unidades de píxeles por segundo
        velocity = acceleration * dt;

        // Actualizamos la posición en unidades de píxeles
        position = velocity * dt;
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
