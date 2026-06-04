#pragma once
#include "Affector.h"

class GravitationalEffector : public Affector
{
public:
    GravitationalEffector(): Affector(Vector2{0,0},0),strength{0}{}
    GravitationalEffector(Vector2 position, float size, float strength)
        : Affector(position, size), strength(strength) {}

    void Apply(std::vector<Body>& bodies) override;

    void Draw() override;


private:
    float strength;
};