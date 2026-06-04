#include "Body.h"

// Semi-Explicit Euler Integration (Symplectic Euler)
void Body::Step(float dt) {
    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = { 0, 0 };
}

// Draw the body as a circle
void Body::Draw() const {
    DrawCircleV(position, size, color);
    DrawCircleLinesV(position, size, WHITE);
}

// Add force to the body (F = ma, so a = F/m)
void Body::AddForce(Vector2 force, ForceMode forceMode) {
    if (bodyType != Bodytype::Dynamic) return;

    switch (forceMode) {
        case ForceMode::Force:
            force = force * inverseMass; // F = ma -> a = F/m
            break;
        case ForceMode::Impulse:
            velocity += force * inverseMass; // Impulse
            break;
        case ForceMode::Acceleration:
            break;
        case ForceMode::VelocityChange:
            velocity += force; // Directly change velocity
            break;
        default:
            break;
    }
    acceleration += force / mass;
}