#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody
{
public:
    RigidBody(){
        mass = UNIT_MASS;
        gravity = GRAVITY;
    }


    inline void setMass( float newMass ){ mass = newMass; }
    inline void setGravity( float newGravity ){ gravity = newGravity; }

    //Force
    inline void ApplyForces( Vector2D f ){ force = f;             }
    inline void ApplyForceX( float fx   ){ force.x = fx;          }
    inline void ApplyForceY( float fy   ){ force.y = fy;          }
    inline void unsetForce()             { force = Vector2D(0,0); }

    //Friction
    inline void ApplyFriction(Vector2D fr){friction = fr;}
    inline void unsetFriction(){friction = Vector2D(0,0);}

    //Update methods
    inline float    getMass     (){ return mass;        }
    inline Vector2D getPosition    (){ return position;    }
    inline Vector2D getVelocity    (){ return velocity;    }
    inline Vector2D getAcceleration(){ return acceleration;}

    void update(float dt){
        acceleration.x = (force.x + friction.x) / mass;
        acceleration.y = (force.y + gravity) / mass;
        velocity  = acceleration * dt;
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
