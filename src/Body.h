#pragma once
#include "raylib.h"
#include "raymath.h"

enum Bodytype {
    Static,
    Kinematic,
    Dynamic
};

enum class ForceMode {
    Force,
    Impulse,
    Acceleration,
	VelocityChange
};

struct Body {

    Bodytype bodyType =  Bodytype::Dynamic;
    Vector2 position{0,0};
    Vector2 Velocity{ 0,0 };
    Vector2 acceleration{ 0,0 };
    float size =1.0f;
    float mass = 1.0f;
    float restitution = 1.0f;
    float gravityScale = 1.0f;
    float damping = 0.0f;
	float inverseMass = 1.0f; // Precompute inverse mass for efficiency (1/mass)
    // Methods
 
    void Step(float dt);
    void Draw() const;
    void AddForce(Vector2 force, ForceMode forceMode = ForceMode::Force);
};