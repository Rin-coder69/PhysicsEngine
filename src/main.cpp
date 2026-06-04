/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
#define RAYGUI_IMPLEMENTATION

#include "RayGui.h"
#define GUI_PHYSICS_IMPLEMENTATION
#pragma warning(push)
#pragma warning(disable: 4576)
#include "gui_Physics.h"
#pragma warning(pop)

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include <vector>






#include "Body.h"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "World.h"
#include "Random.h"
#include "Pointaffector.h"
#include "gravitation_effector.h"
#include "area_effector.h"
#include "drag_effector.h"
#include "Affector.h"
#include "World.h"
#include "world_camera.h"
#include "spring.h"
#include <string>

GuiPhysicsState state;



void AddBody(World& world, Random random, WorldCamera& camera)
{
	Body body;



	body.bodyType = (Bodytype)state.BodyTypeActive;
	body.position = camera.ScreenToWorld(GetMousePosition());
	float angle = random.GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);



	body.AddForce(direction * state.BodyVelocityValue, ForceMode::VelocityChange);//(50.0f + (random.GetRandomFloat() * 500)), ForceMode::VelocityChange);



	//body.velocity = Vector2Scale(direction, random.GetRandomFloat() * 300);//direction * (GetRandomFloat() * 500);
	//body.acceleration = Vector2{ 0, 0 };
	body.size = state.BodySizeValue;//5.0f + (random.GetRandomFloat() * 20.0f);
	body.restitution = state.BodyRestitutionValue;//0.75f + (random.GetRandomFloat() * 0.5f);
	body.mass = body.size * state.BodyMassValue;
	body.inverseMass = (body.bodyType == Bodytype::Static) ? 0 : 1.0f / body.mass;
	body.gravityScale = state.BodyGravityValue;
	body.damping = state.BodyDampingValue;
	//body.color = ColorFromHSV(GetRandomValue(360.0f);



	world.AddBody(body);
}



void AddEffector(World& world, WorldCamera& camera)
{
	Vector2 position = camera.ScreenToWorld(GetMousePosition());
	// using body size instead of effect body size
	float size = state.BodySizeValue * 0.5f;
	Affector* effector = nullptr;
	switch ((AffectorType)state.EffectorTypeActive)
	{
	case(AffectorType::Area):
		effector = (new AreaEffector(position, state.EffectorSizeValue, 0, 10.0f));
		break;
	case(AffectorType::Drag):
		effector = (new DragEffector(position, state.EffectorSizeValue, 1.0f));
		break;
	case(AffectorType::Gravitation):
		effector = (new GravitationalEffector(position, state.EffectorSizeValue, 300.0f));
		break;
	case(AffectorType::Point):
		effector = (new PointEffector(position, state.EffectorSizeValue, 10.0f));
		break;
	default:
		break;
	}



	if (effector) world.AddAffector(effector);
	//world.AddEffector(new PointEffector(Vector2{ 300,200 }, 200, 10.0f));
	//world.AddEffector(new GravitationalEffector(Vector2{ 900, 600 }, 200, 300.0f));
	//world.AddEffector(new AreaEffector(Vector2{ 900, 200 }, 200, 0 , 10.0f));
	//world.AddEffector(new DragEffector(Vector2{ 300, 600 }, 200, 1.0f));
}





int main()
{
	// Initialization
	SetRandomSeed(5);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1280, 800, "PhysicsEngine");
	state = InitGuiPhysics();
	SearchAndSetResourceDir("resources");
	Random random;

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//SetTargetFPS(10);
	World world;
	WorldCamera world_camera(Vector2{ GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f }, 5);
	world.SetBounds(world_camera.ScreenToWorld({ 0, (float)GetScreenHeight() }), world_camera.ScreenToWorld({ (float)GetScreenWidth(),0 }));
	GuiPhysicsState guiState = InitGuiPhysics();
	Body* selectedBody = nullptr;
	Body* connectedBody = nullptr;

	world.AddAffector(&guiState.pointEffector);
	world.AddAffector(&guiState.gravEffector);
	world.AddAffector(&guiState.areaEffector);
	world.AddAffector(&guiState.dragEffector);
	//world.AddAffector(new PointEffector(Vector2{ 600,600 }, 100, 1000.0f));
	//world.AddAffector(new GravitationalEffector(Vector2{ 700,700 }, 200, 30000.0f));
	//world.AddAffector(new GravitationalEffector(100000.0f));
	//world.AddAffector(new AreaEffector(Vector2{ 900,200 }, 200, 0, 30000.0f));
	//world.AddAffector(new DragEffector(Vector2{ 400,400 }, 150, 0.1f));


	float timeAccum = 0.0f;
	float fixedTimeStep = 1.0f / 60.0f; //0.016 * 60.0 =1.0
	bool simulate = true;

	// Game loop
	while (!WindowShouldClose())
	{
		float dt = fminf(GetFrameTime(), 0.1f);
		Vector2 mousePos = GetMousePosition();
		if (IsKeyPressed(KEY_SPACE)) {
			simulate = !simulate;
		}
		// Input handling - Create bodies
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
			(IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{

			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				AddEffector(world,world_camera);

			}
			else {
				AddBody(world,random,world_camera);
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			selectedBody = world.GetBodyInterest(world_camera.ScreenToWorld(GetMousePosition()));
		}


		// spring
		if (selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = world_camera.ScreenToWorld(GetMousePosition());
				if (IsKeyDown(KEY_LEFT_CONTROL))
				{
					Vector2 force = Spring::GetSpringForce(position, selectedBody->position, 1.0f, 3.0f);
					selectedBody->AddForce(force * -1.0f);
				}
				else
				{
					connectedBody = world.GetBodyInterest(world_camera.ScreenToWorld(GetMousePosition()));
				}
				DrawLineV(world_camera.WorldToScreen(position), world_camera.WorldToScreen(selectedBody->position), BLACK);
			}
			else
			{
				if (selectedBody && connectedBody)
				{
					float distance = Vector2Distance(selectedBody->position, connectedBody->position);
					world.AddSpring(*selectedBody, *connectedBody, distance, state.SpringStiffnessValue);
				}

				selectedBody = nullptr;
				connectedBody = nullptr;
			}
		}

		if (state.SimulateActive) {
			timeAccum += dt;

			while (timeAccum > fixedTimeStep) {
				world.Step(dt);
				timeAccum -= fixedTimeStep;
			}
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




		// Draw
		BeginDrawing();
		ClearBackground(WHITE);

		//DrawText("Hello Raylib", 200, 200, 20, WHITE);
		//DrawTexture(wabbit, 400, 200, WHITE);
		world_camera.Begin();
		world.Draw();
		world_camera.End();
		GuiPhysics(&state);



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