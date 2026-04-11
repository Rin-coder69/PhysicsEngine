#pragma once 
#include "body.h"

inline void ExplictEuler(Body& body, float dt) {

	body.position += body.Velocity * dt;
	body.Velocity += body.acceleration * dt;
	body.Velocity *= (1.0f / (1.0f + body.damping * dt));

}


inline void SemiImplictEuler(Body& body, float dt) {

	body.position += body.Velocity * dt;
	body.Velocity += body.acceleration * dt;
	body.Velocity *= (1.0f / (1.0f + body.damping * dt));

}
