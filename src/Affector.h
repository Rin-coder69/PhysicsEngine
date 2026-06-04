#pragma once
#include "Body.h"
#include <vector>

enum class AffectorType {
	Gravitation,
	Point,
	Area,
	Drag,

};
class Affector {


public:
	Affector(Vector2 position, float size)
    : position(position), size(size) {}
	virtual void Apply(std::vector<Body>& bodies) = 0;
	virtual void Draw();

	void CollectBodiesInside(std::vector<Body>& ibodies, std::vector<Body*>& obodies);
		
		
protected:
	Vector2 position;
	float size;

};

