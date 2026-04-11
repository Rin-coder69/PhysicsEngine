#pragma once
#include "Affector.h"
class GravitationalEffector : public Affector
{
public:
    GravitationalEffector(float strength) : strength(strength) {}

    void Apply(std::vector<Body>& bodies) override;

private:
    float strength;
};