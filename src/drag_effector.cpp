#include "drag_effector.h"

void DragEffector::Apply(std::vector<Body>& bodies)
{
    for (auto& body : bodies)
    {
        // Check if body is within the effector's range
        float distance = Vector2Distance(body.position, position);
        if (distance <= size)
        {
            // Calculate drag force: F_d = -kv
            // Drag force is opposite to the direction of motion
            Vector2 dragForce = Vector2Scale(body.velocity, -dragCoefficient);

            // Apply the drag force to the body
            body.ApplyForce(dragForce);
        }
    }
}

void DragEffector::Draw()
{
    // Draw the drag effector area (e.g., as a semi-transparent circle)
    DrawCircleLines(position.x, position.y, size, YELLOW);
    DrawCircle(position.x, position.y, size, Fade(SKYBLUE, 0.2f));
}