#pragma once

#include "raylib.h"
#include "resource_dir.h"
// Returns a random float between 0 and 1

class Random {
public:
	inline float GetRandomFloat(float max) {
		return GetRandomValue(0, max);
	}



	inline float GetRandomFloat(float min, float max) {
		return GetRandomValue(min, max);
	}



	inline float GetRandomFloat() {
		return GetRandomValue(0, 10000) / (float)10000;
	}
};