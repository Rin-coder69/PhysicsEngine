/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "World.h"
#include "Random.h"
#include "Pointaffector.h"
#include "gravitation_effector.h"
#include <string>

int main()
{
    // Initialization
    SetRandomSeed(5);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Hello Raylib");
    SearchAndSetResourceDir("resources");

    Texture wabbit = LoadTexture("wabbit_alpha.png");

    //SetTargetFPS(10);
    World world;

    world.AddAffector(new PointEffector(Vector2{ 200,200 }, 100, 30000.0f));
    world.AddAffector(new PointEffector(Vector2{ 600,600 }, 100, 1000.0f));
	world.AddAffector(new GravitationalEffector(100000.0f));
    float timeAccum = 0.0f;
    float fixedTimeStep = 1.0f / 60.0f; //0.016 * 60.0 =1.0
    // Game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // Input handling - Create bodies
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
            (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
        {
            Body body;

			body.bodyType = (IsKeyDown(KEY_LEFT_ALT)) ? Bodytype::Static : Bodytype::Dynamic;
            body.position = GetMousePosition();

            float angle = GetRandomFloat() * (2 * PI);
            Vector2 direction = { cosf(angle), sinf(angle) };

            body.Velocity = direction * GetRandomFloat(500.0f);
            body.acceleration = { 0, 0 };
            body.size = GetRandomFloat(5.0f, 25.0f);
            body.restitution = GetRandomFloat(0.5f, 1.0f);
            body.mass = 1.0f;
			body.inverseMass = (body.bodyType == Bodytype::Dynamic) ? 1.0f / body.mass : 0.0f;
            body.gravityScale = 1.0f;
            body.damping = 1.0f;
			body.mass = body.size; // Mass proportional to size for more realistic physics

            world.AddBody(body);
        }

        timeAccum += dt;
        while (timeAccum > fixedTimeStep) {
            world.Step(dt);
            timeAccum -= fixedTimeStep;
        }


        std::string fpsText = "FPS: ";
        fpsText += std::to_string(GetFPS());

        DrawText(fpsText.c_str(), 100, 100, 20, GREEN);
        // Input handling - Mouse attractor
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            for (auto& body : world.GetBodies())
            {
                Vector2 direction = mousePos - body.position;
                if (Vector2Length(direction) <= 100.0f)
                {
                    Vector2 force = Vector2Normalize(direction) * 3000.0f;
                    body.AddForce(force);
                }
            }
        }

        // Update
        world.Step(dt);
       

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        //DrawText("Hello Raylib", 200, 200, 20, WHITE);
        //DrawTexture(wabbit, 400, 200, WHITE);

        world.Draw();
       
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            DrawCircleLinesV(mousePos, 100, WHITE);
        }

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(wabbit);
    CloseWindow();

    return 0;
}