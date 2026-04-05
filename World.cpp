#include "World.h"
#include "raymath.h"

World::World() {
    gravity = { 0, 9.18f };
    bodies.reserve(1000);
}

void World::Step(float dt) {
    // Reset accelerations
    for (auto& body : bodies) {
        body.acceleration = Vector2{ 0, 0 };
    }

    // Apply gravity to all bodies
    ApplyGravity();

    // Update all bodies (integration)
    for (auto& body : bodies) {
        body.Step(dt);
    }

    // Handle collisions with screen boundaries
    HandleCollisions();
}

void World::Draw() {
    for (const auto& body : bodies) {
        body.Draw();
    }
}

void World::AddBody(const Body& body) {
    bodies.push_back(body);
}

void World::SetGravity(Vector2 newGravity) {
    gravity = newGravity;
}

Vector2 World::GetGravity() const {
    return gravity;
}

std::vector<Body>& World::GetBodies() {
    return bodies;
}

void World::ApplyGravity() {
    for (auto& body : bodies) {
        body.AddForce(gravity * 100.0f);
    }
}

void World::HandleCollisions() {
    for (auto& body : bodies) {
        // Right wall collision
        if (body.position.x + body.size > GetScreenWidth()) {
            body.position.x = GetScreenWidth() - body.size;
            body.Velocity.x *= -body.restitution;
        }

        // Left wall collision
        if (body.position.x - body.size < 0) {
            body.position.x = body.size;
            body.Velocity.x *= -body.restitution;
        }

        // Bottom wall collision
        if (body.position.y + body.size > GetScreenHeight()) {
            body.position.y = GetScreenHeight() - body.size;
            body.Velocity.y *= -body.restitution;
        }

        // Top wall collision
        if (body.position.y - body.size < 0) {
            body.position.y = body.size;
            body.Velocity.y *= -1.0f;
        }
    }
}