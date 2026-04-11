#pragma once
#include "Body.h"
#include <vector>

class Affector {
public:
	virtual void Apply(std::vector<Body>& bodies) = 0;
		virtual void Draw() {
		
		}
};
