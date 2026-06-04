#include "Affector.h"

void Affector::Draw() {
    DrawCircleLinesV(position, size, WHITE);
}

void Affector::CollectBodiesInside(std::vector<Body>& ibodies, std::vector<Body*>& obodies)
{
    for (auto& body : ibodies) {
        if (Vector2DistanceSqr(body.position, position) < (size * size)) {
            obodies.push_back(&body);
        }
    }
}
