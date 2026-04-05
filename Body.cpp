#include "Body.h"

// Semi-Explicit Euler Integration (Symplectic Euler)
void Body::Step(float dt) {
    Velocity += acceleration * dt;
    position += Velocity * dt;
    acceleration = { 0, 0 };
}

// Draw the body as a circle
void Body::Draw() const {
    DrawCircleV(position, size, RED);
}

// Add force to the body (F = ma, so a = F/m)
void Body::AddForce(Vector2 force) {
    acceleration += force / mass;
}