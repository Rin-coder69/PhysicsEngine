#pragma once

#include "raylib.h"

// Returns a random float between 0 and 1
inline float GetRandomFloat()
{
    return GetRandomValue(0, 10000) / (float)10000;
}

// Returns a random float between 0 and max
inline float GetRandomFloat(float max)
{
    return GetRandomFloat() * max;
}

// Returns a random float between min and max
inline float GetRandomFloat(float min, float max)
{
    return min + GetRandomFloat() * (max - min);
}
