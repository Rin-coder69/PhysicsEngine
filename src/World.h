#pragma once
#include "collision.h"
#include "Body.h"
#include "raylib.h"
#include <vector>
#include "Affector.h"
#include "spring.h"
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
    
   
    void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }



    
    


    Body* GetBodyInterest(const Vector2& postition);
    void AddSpring(Body& bodyA, Body& bodyB, float restLength, float stiffness);

    // Getters/Setters
    void SetGravity(Vector2 newGravity);
    static void SetSpringMultiplier(float multiplier) {springMult}
    Vector2 GetGravity() const;
    std::vector<Body>& GetBodies();

private:
    void UpdateCollision();

private:

    static Vector2 Gravity;
    // Internal physics methods
    

        Vector2 boundsMin{ -10.0f, -5.0f };
        Vector2 boundsMax{ 10.0f, 5.0f };
    
   
    std::vector<class Spring*> springs;

    void ApplyGravity();
    void HandleCollisions();
};