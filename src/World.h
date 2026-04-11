#pragma once
#include "collision.h"
#include "Body.h"
#include "raylib.h"
#include <vector>
#include "Affector.h"

class World {
private:
    std::vector<Body> bodies;
        Vector2 gravity{ 0, 9.18f };

    // Remove duplicate bodies declaration and fix affectors to store pointers
    std::vector<class Affector*> affectors;
    std::vector<Contact> contacts;

public:
    World();

    // Main update and rendering methods
    void Step(float dt);
    void Draw();
	void updateCollisions();

    // Body management
    void AddBody(const Body& body);
    void AddAffector(Affector* affector);

    // Getters/Setters
    void SetGravity(Vector2 newGravity);
    Vector2 GetGravity() const;
    std::vector<Body>& GetBodies();

private:
    // Internal physics methods
    void ApplyGravity();
    void HandleCollisions();
};