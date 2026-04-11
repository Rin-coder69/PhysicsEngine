#pragma once
#include "Affector.h"

class PointEffector : public Affector {
public:
	PointEffector(Vector2 position, float size, float forceMagnitude) :
		position{ position },
		size{ size },
		forceMagnitude{ forceMagnitude }
	{}
	
	void Apply(std::vector<Body>& bodies) override;
	void Draw();
private:
	Vector2 position;
	float size;
	float forceMagnitude;
};