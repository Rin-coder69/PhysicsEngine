#pragma once

#include "Body.h"
#include "raylib.h"
#include <vector>

class World {
private:
    std::vector<Body> bodies;
    Vector2 gravity;

public:
    World();

    // Main update and rendering methods
    void Step(float dt);
    void Draw();

    // Body management
    void AddBody(const Body& body);

    // Getters/Setters
    void SetGravity(Vector2 newGravity);
    Vector2 GetGravity() const;
    std::vector<Body>& GetBodies();

private:
    // Internal physics methods
    void ApplyGravity();
    void HandleCollisions();
};