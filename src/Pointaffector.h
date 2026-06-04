#pragma once
#include "Affector.h"

class PointEffector : public Affector {
public:
    PointEffector() : Affector(Vector2{ 0,0 }, 0), forceMagnitude{ 0 } {}
    PointEffector(Vector2 position, float size, float forceMagnitude)
        : Affector(position, size), forceMagnitude{ forceMagnitude }
    {}

    void Apply(std::vector<Body>& bodies) override;
    void Draw();
private:
    float forceMagnitude;
};