#include "World.h"
#include "Affector.h"
#include "raymath.h"
#include <iostream>
#include "Body.h"
#include "Pointaffector.h"
#include "spring.h"

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
            body.position += body.velocity * dt;
        }
    }

   

    for (auto& affector : affectors) affector->Apply(bodies);
    for (auto& body : bodies) body.AddForce(gravity * body.gravityScale, ForceMode::Acceleration);

    // Apply gravity to all bodies
    //ApplyGravity();

    // Update all bodies (integration)
    for (auto& body : bodies) {
        if (body.bodyType == Bodytype::Dynamic) {
            body.Step(dt);
        }
    }
    for (auto& spring : springs) spring->Apply(1.0f);

    // Handle collisions with screen boundaries
    //HandleCollisions();
   for(int i =0; i < 4; i++) updateCollisions();
}

void World::Draw() {

    /*
    DrawLineV(Vector2{0,boundsMin.y},Vector2{0,bounds})

    for (auto& spring : springs) spring->Draw();
    for (const auto& body : bodies) {
        body.Draw(); bodies apply function applt to world corrd
    }

    for (auto& affectors : affectors) affectors->Draw();
    */
    for (auto& affector : affectors) affector->Draw();
    for (auto& body : bodies) body.Draw();
    for (auto& spring : springs) spring->Draw();

}



void World::updateCollisions()
{
    contacts.clear();
    CreateContacts(bodies, contacts);
    SeparateContacts(contacts);
	ResolveContacts(contacts);

    // collision
    for (auto& body : bodies)
    {
        if (body.position.x + body.size > boundsMax.x)
        {
            body.position.x = boundsMax.x - body.size;
            body.velocity.x *= -body.restitution;
        }
        if (body.position.x - body.size < boundsMin.x)
        {
            body.position.x = boundsMin.x + body.size;
            body.velocity.x *= -body.restitution;
        }
        if (body.position.y + body.size > boundsMax.y)
        {
            body.position.y = boundsMax.y - body.size;
            body.velocity.y *= -body.restitution;
        }
        if (body.position.y - body.size < boundsMin.y)
        {
            body.position.y = boundsMin.y + body.size;
            body.velocity.y *= -body.restitution;
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

Body* World::GetBodyInterest(const Vector2& position)
{
    for (auto& body : bodies) {
        if (CheckCollisionPointCircle(position, body.position, body.size)) {
            return &body;
        }
    }
    return nullptr;
}

void World::AddSpring(Body& bodyA, Body& bodyB, float restLength, float stiffness) {
    Spring* spring = new Spring(&bodyA, &bodyB, restLength, stiffness);
    springs.push_back(spring);
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
            body.velocity.x *= -body.restitution;
        }

        // Left wall collision
        if (body.position.x - body.size < 0) {
            body.position.x = body.size;
            body.velocity.x *= -body.restitution;
        }

        // Bottom wall collision
        if (body.position.y + body.size > GetScreenHeight()) {
            body.position.y = GetScreenHeight() - body.size;
            body.velocity.y *= -body.restitution;
        }

        // Top wall collision
        if (body.position.y - body.size < 0) {
            body.position.y = body.size;
            body.velocity.y *= -1.0f;
        }
    }
}