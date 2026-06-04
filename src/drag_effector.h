#pragma once
#include "Affector.h"

class DragEffector : public Affector
{
public:
    DragEffector() : Affector(Vector2{ 0,0 }, 0), dragCoefficient{ 0 } {}
    DragEffector(Vector2 position, float size, float dragCoefficient)
        : Affector(position, size), dragCoefficient(dragCoefficient) {
    }

    void Apply(std::vector<Body>& bodies) override;
    void Draw() override;

private:
    float dragCoefficient;
};