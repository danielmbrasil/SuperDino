//
// Created by Daniel M Brasil on 6/27/20.
//

#ifndef RigidBody_H
#define RigidBody_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.81f

class RigidBody {
public:
    RigidBody() {
        m_Mass = UNI_MASS;
        m_Gravity = GRAVITY;
    }

    inline Vector2D& getPosition() {
        return m_Position;
    }

    inline Vector2D& getVelocity() {
        return m_Velocity;
    }

    inline Vector2D& getAcceleration() {
        return m_Acceleration;
    }

    inline void setMass(float m) {
        m_Mass = m;
    }

    inline void setGravity(float g) {
        m_Gravity = g;
    }

    inline void applyForce(Vector2D& F) {
        m_Force = F;
    }

    inline void applyForceX(float Fx) {
        m_Force.x = Fx;
    }

    inline void applyForceY(float Fy) {
        m_Force.y = Fy;
    }

    inline void zeroForce() {
        m_Force.Zero();
    }

    inline void applyFriction(Vector2D& Fx) {
        m_Friction = Fx;
    }

    inline void zeroFriction() {
        m_Friction.Zero();
    }

    void update(float delta) {
        m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
        m_Acceleration.y = m_Gravity + m_Force.y/m_Mass;
        m_Velocity = m_Acceleration * delta;
        m_Position = m_Velocity * delta;
    }

private:
    float m_Mass;
    float m_Gravity;

    Vector2D m_Force;
    Vector2D m_Friction;
    Vector2D m_Position;
    Vector2D m_Velocity;
    Vector2D m_Acceleration;
};


#endif //RigidBody_H
