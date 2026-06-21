#pragma once

struct SimParams {
    float maxSpeed = 100.0f;
    float minSpeed = 40.0f;
    float perceptionRadius = 100.0f;
    float separationRadius = 20.0f;
    float avoidFactor = 3.0f;
    float alignmentFactor = 1.0f;
    float cohesionFactor = 1.0f;
    float edgeMargin = 50.0f;
    float turnFactor = 1.0f;
};
