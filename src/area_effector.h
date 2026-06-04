#pragma once
#include "Affector.h"

class AreaEffector : public Affector {
public:
    AreaEffector() : Affector(Vector2{ 0,0 }, 0), forceMagnitude{ 0 } {}
    AreaEffector(Vector2 position, float size, float angle, float forceMagnitude)
        : Affector(position, size), angle(angle), forceMagnitude{ forceMagnitude }
    {
    }

    void Apply(std::vector<Body>& bodies) override;
    void Draw();
private:
    float angle;
    float forceMagnitude;
};