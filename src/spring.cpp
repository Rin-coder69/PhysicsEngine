#include "spring.h"
#include "Body.h"

void Spring::Apply(float multiplier) {
	Vector2 force = GetSpringForce(bodyA->position, bodyB->position, restLength, stiffness * multiplier);

	bodyA->AddForce(force);
	bodyB->AddForce(force * -1.0f);
}

void Spring::Draw() {
	DrawLineV(bodyA->position, bodyB->position, BLACK);
}




//returns the force that pulls B to A
Vector2 Spring::GetSpringForce(Vector2 positionA, Vector2 positionB, float restLength, float stiffness)

{

	Vector2 direction = positionA - positionB;

	float length = Vector2Length(direction);

	float displacement = length - restLength;

	//f = -kx (k = stiffness | x = displacement)

	float magnitude = -(displacement * stiffness);

	return Vector2Normalize(direction) * magnitude;

}
