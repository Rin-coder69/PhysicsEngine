#include "World.h"
#include "Affector.h"
#include "raymath.h"
#include <iostream>
#include "Body.h"
#include "Pointaffector.h"

World::World() {
    gravity = { 0, 9.8f };
    bodies.reserve(1000);
}

void World::Step(float dt) {
    // Reset accelerations
    /*for (auto& body : bodies) {
        body.acceleration = gravity * body.gravityScale * 100.0f;

    }*/

    for (auto& body : bodies) {
        if (body.bodyType == Bodytype::Kinematic) {
            body.position += body.Velocity * dt;
        }
    }

    //for (auto& affector : affectors) affector->Apply(bodies);

    // Apply gravity to all bodies
    ApplyGravity();

    // Update all bodies (integration)
    for (auto& body : bodies) {
        if (body.bodyType == Bodytype::Dynamic) {
            body.Step(dt);
        }
    }

    // Handle collisions with screen boundaries
    //HandleCollisions();
    updateCollisions();
}

void World::Draw() {
    for (const auto& body : bodies) {
        body.Draw();
    }

    for (auto& affectors : affectors) affectors->Draw();
}



void World::updateCollisions()
{
    contacts.clear();
    CreateContacts(bodies, contacts);
    SeparateContacts(contacts);

    // collision
    for (auto& body : bodies)
    {
        if (body.position.x + body.size > GetScreenWidth())
        {
            body.position.x = GetScreenWidth() - body.size;
            body.Velocity.x *= -body.restitution;
        }
        if (body.position.x - body.size < 0)
        {
            body.position.x = body.size;
            body.Velocity.x *= -body.restitution;
        }
        if (body.position.y + body.size > GetScreenHeight())
        {
            body.position.y = GetScreenHeight() - body.size;
            body.Velocity.y *= -body.restitution;
        }
        if (body.position.y - body.size < 0)
        {
            body.position.y = body.size;
            body.Velocity.y *= -body.restitution;
        }
    }
}

void World::AddBody(const Body& body) {
    bodies.push_back(body);
}

void World::AddAffector(Affector* affector)
{
    affectors.push_back(affector);
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