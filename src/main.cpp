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

int main()
{
    // Initialization
    SetRandomSeed(5);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Hello Raylib");
    SearchAndSetResourceDir("resources");

    Texture wabbit = LoadTexture("wabbit_alpha.png");
    World world;

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
            body.position = mousePos;

            float angle = GetRandomFloat() * (2 * PI);
            Vector2 direction = { cosf(angle), sinf(angle) };

            body.Velocity = direction * GetRandomFloat(500.0f);
            body.acceleration = { 0, 0 };
            body.size = GetRandomFloat(5.0f, 25.0f);
            body.restitution = GetRandomFloat(0.5f, 1.0f);
            body.mass = 1.0f;

            world.AddBody(body);
        }

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

        DrawText("Hello Raylib", 200, 200, 20, WHITE);
        DrawTexture(wabbit, 400, 200, WHITE);

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